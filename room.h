#ifndef ROOM_H
#define ROOM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct room{
	char* name;
	int* residents;
	int num_residents;
} Room;
typedef struct brother{
	char* firstname;
	char* lastname;
	int points;
	int index;
} Brother;
Room* make_room(char* name, int residents[], int len);
void free_room(Room* room);
int check_take_room(char* message);
int total_points(Room* room, Brother** brothers);
Room* room_from_message(char* message);
int check_can_take(char* message, Brother** brothers, Room** rooms);
int take_room(char* message, Brother** brothers, Room** rooms);
Room* get_room(char* room_name, Room** rooms);
#endif