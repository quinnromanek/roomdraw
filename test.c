#include "room.h"
#include "csvparser.h"

int main(void) {
	printf("\nRunning tests\n\n");
	printf("Testing room.h:\n");
	Room* room;
	int res[] = {1, 2};
	
	if((room = make_room("3b", res, 2)) == NULL) {
		printf("error: make_room failed to return a real value.\n");
		return -1;
	}else{
		printf("Test passed: Room did not return null.\n");
	}
	if(strcmp(room->name, "3b") != 0) {
		printf("error: name is incorrect.\n");
	}else{
		printf("Test passed: name is correct.\n");
	}
	if(room->num_residents != 2) {
		printf("error: number of residents is incorrect\n");
	}else{
		printf("test passed: residents is correct.\n");
	}

	// CSV tests.
	Brother** brothers;
	brothers = load_csv("points.csv");
	printf("loaded csv correctly\n");
	printf("%s\n", (brothers[0])->firstname);
	free_brother_list(brothers);
	free(room);



	return 0;
}