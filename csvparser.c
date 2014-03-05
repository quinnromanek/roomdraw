
#include "csvparser.h"

static Brother* load_brother(char* line) {
	Brother* new_brother;
	new_brother = (Brother*) malloc(sizeof(Brother));
	char* token;
	token = strtok(line, ",\n");

	new_brother->firstname = strdup(token);
	//printf("%s\n", new_brother->firstname);
	token = strtok(NULL, ",\n");
	new_brother->lastname = strdup(token);
	//printf("%s\n", new_brother->lastname);
	token = strtok(NULL, ",\n");
	new_brother->points = atoi(token);


	return new_brother;
} 
Brother** load_brother_csv(const char* filename) {
	FILE* csv_file;
	int file_len, i;
	file_len =0;
	i=0;
	csv_file = fopen(filename, "r");
	if(csv_file == NULL) {
		printf("Error: Could not open file\n");
		return NULL;
	}
	char line[1024];
	//Cut off headers:
	fgets(line, 1024, csv_file);
	while(fgets(line, 1024, csv_file) != NULL) {
		file_len++;
		//printf("Line %d: %s\n", file_len, line);
	}
	Brother** list = (Brother**) malloc(sizeof(Brother*)*(file_len+1));
	rewind(csv_file);
	fgets(line, 1024, csv_file);
	while(fgets(line, 1024, csv_file)) {
		char* tmp = strdup(line);

		list[i] = load_brother(tmp);
		list[i]->index = i;

		i++;
	}
	list[++i] = NULL;
	fclose(csv_file);
	return list;

}

void free_brother_list(Brother** list) {
	int i;
	i=0;
	while(list[i] != NULL) {
		free(list[i]->firstname);
		free(list[i]->lastname);
		free(list[i]);
		i++;		
	}
	free(list);
}
Room** load_room_csv(const char* filename) {
	FILE* csv_file;
	int file_len, i;
	file_len = i = 0;
	csv_file = fopen(filename, "r");
	if(csv_file == NULL) {
		printf("Error: Could not open file\n");
		return NULL;
	}
	char line[1024];
	fgets(line, 1024, csv_file);
	while(fgets(line, 1024, csv_file) != NULL) {
		file_len++;
	}
	Room** list = (Room**) malloc(sizeof(Room*)*(file_len+1));
	rewind(csv_file);
	fgets(line, 1024, csv_file);
	while(fgets(line, 1024, csv_file) != NULL) {
		int init[] = {-1, -1, -1, -1};
		char* tmp = strdup(line);
		char* token;
		token = strtok(tmp, ",\n");
		int num = atoi(strtok(NULL, ",\n"));
		list[i] = make_room(token, init, num);
		i++;

	}
	list[++i] = NULL;
	fclose(csv_file);
	return list;

}