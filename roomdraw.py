import csv
class Room: 
	def __init__(self, members):
		self.size = members
		self.occupants = []

	def occupy(self, new_occupants):
		if len(new_occupants) is not self.size:
			return False
		self.occupants = new_occupants
		return True

	def total_points(self):
		points = 0
		for brother in self.occupants:
			points += brother[1]

		return points

	def can_take(self, occupants):
		taking_points = 0
		for brother in occupants:
			taking_points += brother[1]

		return (taking_points > self.total_points()) and len(occupants) == self.size

	def try_take(self, occupants):
		result = self.can_take(occupants)
		if result:
			self.occupy(occupants)
		return result

	def __repr__(self):
		val = ""
		if len(self.occupants) == 0:
			return "No one is in this room."
		for brother in self.occupants:
			val += "{0}: {1} pts".format(brother[0].capitalize(), brother[1])

		return val

ROOMS = {}
BROTHERS = {}
doubles = ['2a', '2e', '2f', '2h', '2i', '3a', '3e', '3f', '3h', '3i', 'c1']
triples = ['2b', '2d', '3b', '3d']
quads = ['2c', '3c']
singles = ['c2', '2g', '3g']
for d in doubles:
	ROOMS[d] = Room(2)

for t in triples:
	ROOMS[t] = Room(3)

for q in quads:
	ROOMS[q] = Room(4)

for s in singles:
	ROOMS[s] = Room(1)

with open('points.csv', 'rb') as file:
	reader = csv.reader(file)
	for row in reader:
		BROTHERS[row[1].lower()] = int(row[2])
global run
run = True
while run:

	text = raw_input("~>")
	args = text.split()
	name = args[0]
	if name == "end":
		print("Goodbye")
		break
	elif name == "room":
		try:
			print(ROOMS[args[1]])
		except KeyError:
			print "Error: Unrecognized Room Name"
	elif name == "points":
		try:
			print("{0}: {1} points".format(args[1], BROTHERS[args[1].lower()]))
		except KeyError:
			print "Error: Unknown Brother.  Make sure to only use last names."
	elif name == "take":
		brothers = args[2:]
		occupants = []
		room = ROOMS[args[1]]
		for b in brothers:
			occupants.append([b.lower(), BROTHERS[b.lower()]])

		result = room.try_take(occupants)
		if result == True:
			word = "{0} taken by ".format(args[1])
			for b in brothers:
				word += (b + " ")
			print word
		else:
			print("Not enough points/incorrect people to take this room.")
	elif name == "check":
		brothers = args[2:]
		occupants = []
		room = ROOMS[args[1]]
		for b in brothers:
			occupants.append([b.lower(), BROTHERS[b.lower()]])
		result = room.can_take(occupants)
		if result:
			print("It's possible to take {0} with these brothers.".format(args[1]))
		else:
			print("Not enough points.")





