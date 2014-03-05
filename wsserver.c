#include <stdio.h>
#include <stdlib.h>
#include <libwebsockets.h>
#include <string.h>

static int counter = 1;
static int callback_http(struct libwebsocket_context* this, struct libwebsocket* wsi,
			enum libwebsocket_callback_reasons reason, void* user,
			void* in, size_t len) 
{
	switch(reason) {
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			printf("Http connection established\n");
			break;
		case LWS_CALLBACK_HTTP: {
			char* uri;
			uri = (char*) in;
			printf("Requested uri: %s\n", uri);
			if(strcmp(uri, "/roomconfig.csv")== 0) {
				libwebsockets_serve_http_file(this, wsi, "roomconfig.csv", "text/csv",
					"Access-Control-Allow-Origin: null\n");
			}else if(strcmp(uri, "/points.csv") == 0) {
				libwebsockets_serve_http_file(this, wsi, "points.csv", "text/csv",
					"Access-Control-Allow-Origin: null\n");
			}
		}
			break;
		default: break;
	}	

	//libwebsocket_close_and_free_session(this, wsi, LWS_CLOSE_STATUS_NORMAL);
	return 0;
}
static int callback_dumb_increment(struct libwebsocket_context* this, struct libwebsocket* wsi,
	enum libwebsocket_callback_reasons reason, void* user,
	void* in, size_t len)
{
	switch(reason) {
		case LWS_CALLBACK_ESTABLISHED:
			printf("connection established\n");
			break;
		case LWS_CALLBACK_RECEIVE: {
			int i;
			char response [33];
			sprintf(response, "%d", counter);
			counter++;
			unsigned char* buf = (unsigned char*) malloc(LWS_SEND_BUFFER_PRE_PADDING + strlen(response) + LWS_SEND_BUFFER_POST_PADDING);
			for (i = 0; i<len; i++) {
				buf[LWS_SEND_BUFFER_PRE_PADDING + i] = response[i];
			}
			printf("received data: %s, replying %.*s\n", (char*) in, (int) strlen(response), buf+LWS_SEND_BUFFER_PRE_PADDING);
			libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], strlen(response), LWS_WRITE_TEXT);

			free(buf);
			break;
		}
		default:
			break;

	}
	return 0;
}

static int callback_room_config(struct libwebsocket_context* this, struct libwebsocket* wsi,
	enum libwebsocket_callback_reasons reason, void* user, void* in, size_t len)
{
	switch(reason) {

	}
}

static struct libwebsocket_protocols protocols[] = {
	{
		"http-only",
		callback_http,
		0
	},
	{
		"dumb-increment-protocol",
		callback_dumb_increment,
		0
	},
	{ NULL, NULL, 0}
};

int main(void) {
	struct libwebsocket_context *context;
	// Describe the parameters of the server context
	struct lws_context_creation_info info;
	info.port = 9000;
	info.iface = NULL;
	info.protocols = protocols;
	info.extensions = libwebsocket_get_internal_extensions();
	info.ssl_cert_filepath = NULL;
	info.ssl_private_key_filepath = NULL;
	info.gid = -1;
	info.uid = -1;
	info.options = 0;
	printf("Creating context\n");
	context = libwebsocket_create_context(&info);

	if(context == NULL) {
		fprintf(stderr, "libwebsocket init failed\n");
		return -1;
	}
	printf("Starting Server...\n");
	while(1) {
		libwebsocket_service(context, 50); // Process all events then wait 50ms
	}
	libwebsocket_context_destroy(context);

	return 0;
}