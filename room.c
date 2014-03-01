#include "room.h"

Room* make_room(char* name, int residents[], int len) {
	if(len > 4) {
		return NULL;
	}
	int i;
	Room* new_room = (Room*) malloc(sizeof(Room));
	new_room->name = name;
	for(i = 0; i<len; i++) {
		new_room->residents[i]= residents[i];
	}
	new_room->num_residents = len;
	return new_room;
}