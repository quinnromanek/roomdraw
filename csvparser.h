#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

Brother** load_brother_csv(const char* filename);
Room** load_room_csv(const char* filename);
void free_brother_list(Brother** list);


#endif