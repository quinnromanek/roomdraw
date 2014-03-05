#include "room.h"

Room* make_room(char* name, int residents[], int len) {
	if(len > 4) {
		return NULL;
	}
	int i;
	Room* new_room = (Room*) malloc(sizeof(Room));
	new_room->name = name;
	new_room->residents = (int*) malloc(sizeof(int)*len);
	for(i = 0; i<len; i++) {
		new_room->residents[i]= residents[i];
	}
	new_room->num_residents = len;
	return new_room;
}
void free_room(Room* room) {
	free(room->residents);
	free(room);
}
Room* room_from_message(char* message) {
	char* tmp = strdup(message);
	char* room;
	char* residents;
	int resident_list[4];
	room = strtok(tmp, "|");
	residents = strtok(NULL, "|");
	if(residents == NULL){
		printf("Error: incorrectly formatted message.\n");
		return -1;
	}
 	int i = 1;
	char* resident;
	resident_list[0] = atoi(strtok(residents, ","));
	while(resident = strtok(NULL, ",")) {
		resident_list[i] = atoi(resident);
		i++;
	}
	return make_room(room, resident_list, i);
}
int total_points(Room* room, Brother** brothers) {
	int i=0;
	int points = 0;
	for(i=0; i<room->num_residents; i++) {
		if(room->residents[i] == -1) {
			continue;
		}else{
			int brother = room->residents[i];
			points += brothers[brother]->points;
		}
	}
	return points;
}
Room* get_room(char* room_name, Room** rooms) {
	int i;
	for(i = 0; rooms[i] != NULL; i++) {
		if(strcmp(room_name, rooms[i]->name) == 0) {
			return rooms[i];
		}
	}
	printf("Error: room not found.\n");
	return NULL;

}
int check_can_take(char* message, Brother** brothers, Room** rooms) {
	Room* poss_room = room_from_message(message);
	Room* real_room;
	int result;
	if((real_room = get_room(poss_room->name, rooms)) == NULL) {
		free_room(poss_room);
		return 0; // false
	}
	if(poss_room->num_residents != real_room->num_residents) {
		printf("Error: Occupancy info for rooms doesn't match.\n");
		free_room(poss_room);
		return 0;
	}
	result = (total_points(poss_room, brothers) > total_points(real_room, brothers)); 
	free_room(poss_room);
	return result;
}
int take_room(char* message, Brother** brothers, Room** rooms) {
	if (!check_can_take(message, brothers, rooms))
	{
		return 0;
	}
	Room* poss_room = room_from_message(message);
	Room* real_room;
	if((real_room = get_room(poss_room->name, rooms)) == NULL) {
		free_room(poss_room);
		return 0;
	}
	int i = 0;
	for(i = 0; i<real_room->num_residents; i++) {
		real_room->residents[i] = poss_room->residents[i];
	}
	free_room(poss_room);
	return 1;

}