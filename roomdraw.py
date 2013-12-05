import csv

class Person:
	def __init__(self, name, points, room=None):
		self.name = name
		self.points = points
		self.room = room

class Room: 
	def __init__(self, members, name):
		self.size = members
		self.name = name
		self.occupants = []

	def occupy(self, new_occupants):
		if len(new_occupants) is not self.size:
			return False
		for o in self.occupants:
			o.room = None
		for o in new_occupants:
			o.room = self.name
		self.occupants = new_occupants
		return True

	def total_points(self):
		points = 0
		for brother in self.occupants:
			points += brother.points

		return points

	def can_take(self, occupants):
		taking_points = 0
		for brother in occupants:
			taking_points += brother.points

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
			val += "{0}: {1} pts".format(brother.name.capitalize(), brother.points)

		return val

def compare(occupants):
	target = len(occupants)
	names = map(lambda x: x.name, occupants)
	points = 0
	for o in occupants:
		points += o.points
	combos = []
	def comparison(total, depth, already, checked):

		if total > points:
			others = target - depth + 1 
			word = ""
			for a in already:
				word += (a.capitalize() + " ") 
			if(others > 0): word += "and {0} other(s)".format(others)

			print(word)
			return
		elif depth > target:
			return
		local_checked = []
		for b in BROTHERS:
			bro = BROTHERS[b]
			if bro.room != None or bro.name in names or bro.name in already or bro.name in checked: continue
			comparison(total + bro.points, depth + 1, already + [bro.name], checked + local_checked)
			local_checked.append(bro.name)

	comparison(0, 1, [], [])


	

ROOMS = {}
BROTHERS = {}
doubles = ['2a', '2e', '2f', '2h', '2i', '3a', '3e', '3f', '3h', '3i']
triples = ['2b', '2d', '3b', '3d']
quads = ['2c', '3c']
singles = ['c2', 'c1', '2g', '3g']
for d in doubles:
	ROOMS[d] = Room(2, d)

for t in triples:
	ROOMS[t] = Room(3, t)

for q in quads:
	ROOMS[q] = Room(4, q)

for s in singles:
	ROOMS[s] = Room(1, s)

with open('points.csv', 'rb') as file:
	reader = csv.reader(file)
	for row in reader:
		BROTHERS[row[1].lower()] = Person(row[1].lower(), int(row[2]))
		if row[1].lower() in ['koury', 'bernhart']: BROTHERS[row[1].lower()].room = "Out"
global run
run = True
print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
print("~~~     Room Draw Simulator       ~~~")
print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
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
			print("{0}: {1} points".format(args[1], BROTHERS[args[1].lower()].points))
		except KeyError:
			print "Error: Unknown Brother.  Make sure to only use last names."
	elif name == "take":
		brothers = args[2:]
		occupants = []
		room = ROOMS[args[1]]
		for b in brothers:
			occupants.append(BROTHERS[b.lower()])

		result = room.try_take(occupants)
		if result == True:
			word = "{0} taken by ".format(args[1].capitalize())
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
			occupants.append(BROTHERS[b.lower()])
		result = room.can_take(occupants)
		if result:
			print("It's possible to take {0} with these brothers.".format(args[1]))
		else:
			print("Not enough points.")
	elif name == "compare":
		brothers = args[1:]
		occupants = []
		for b in brothers:
			occupants.append(BROTHERS[b.lower()])
		compare(occupants)

	elif name == "compare-room":
		room = ROOMS[args[1]]
		if len(room.occupants) == 0:
			print("No one's in that room!")
		compare(room.occupants)






