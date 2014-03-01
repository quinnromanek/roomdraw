#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>

typedef struct room{
	char* name;
	int residents[4];
	int num_residents;
} Room;

Room* make_room(char* name, int residents[], int len);
#endif