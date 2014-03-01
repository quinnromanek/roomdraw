#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct brother{
	char* firstname;
	char* lastname;
	int points;
	int index;
} Brother;
Brother** load_csv(const char* filename);
void free_brother_list(Brother** list);


#endif