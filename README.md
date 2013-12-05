RoomDraw
========

Room Draw Simulator: 

## Commands

*End*

	end

Closes the progam

*Points*

	points [lastname]

Prints the points of the brother

*Room*

	room [roomname] 

Prints the current occupants of the room and their respective points.

*Check*

	check [roomname] [list of brother lastnames]

Prints whether or not the given list of brothers can take the room. *Squatter points are not accounted for*

*Take*

	take [roomname] [list of brother lastnames]

Takes the room with given brothers if possible, otherwise tells you that the room can't be taken.

*Compare*

	compare [list of brother lastnames]

Prints all the possible combinations of brothers that could take a room from the given list of brothers.   It doesn't take into account brothers that have already taken rooms, however.