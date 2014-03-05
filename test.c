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
	brothers = load_brother_csv("points.csv");
	printf("Loading test: should print all brothers and points\n");
	int i = 0;
	while(brothers[i] != NULL) {
		//printf("%s %s | Points: %d\n", brothers[i]->firstname, brothers[i]->lastname, brothers[i]->points);
		i++;
	}
	printf("Testing room loader\n");
	Room** rooms;
	rooms = load_room_csv("roomconfig.csv");
	i = 0;
	while(rooms[i] != NULL) {

		printf("%s ", rooms[i]->name);
		i++;
	}
	printf("\n");
	printf("Testing total points:\n\n");
	Room* test = room_from_message("3b|-1,-1");
	printf("Should be 3b: 3b=%s\n", test->name);
	printf("Should be 2: 2=%d\n", test->num_residents);
	printf("Should equal zero: 0=%d\n", total_points(test, brothers));
	free_room(test);
	test = room_from_message("2g|45");
	Room* sean = room_from_message("2g|6");
	printf("Should equal 96: 96=%d\n", total_points(test, brothers));
	printf("Should be 1: 1=%d\n", check_can_take("2g|6", brothers, rooms));
	printf("Taking 2g: should be 1, 1=%d\n", take_room("2g|6", brothers, rooms));
	printf("Attempting to take 2g: should be 0, 0=%d\n", check_can_take("2g|45", brothers, rooms));
	printf("Testing occupancy filter, should be 0, 0=%d\n", check_can_take("2g|45,44", brothers,rooms));
	printf("Testing name check, should be zero, 0=%d\n", check_can_take("2z|45,44", brothers, rooms));
	free_brother_list(brothers);
	free(test);



	return 0;
}