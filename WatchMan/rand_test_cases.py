import os, sys, random


def random_even(max_int):
	rand_int = random.randint(1, (max_int / 2) - 1 )
	return 2 * rand_int #ensure even


max_int = int(sys.argv[1])

output = list()

while(len(output) < (max_int)):
	rand_even = random_even(max_int);
	arr = list()
	i = 1
	while(i <= max_int):
		arr.append(i)
		i += 1
	
	random.shuffle(arr)

	result = []

	rand_int1 = random.randint(0, 150)
	rand_int2 = random.randint(0, 150)

	diff = 0;

	row = []

	if(rand_int1 >= rand_int2):
		diff = rand_int1 - rand_int2
		if(diff % 2 != 0):
			rand_int2 += 1
		row = arr[rand_int1 : rand_int2]
	else:
		diff = rand_int2 - rand_int1
		if(diff % 2 != 0):
			rand_int1 += 1
		row = arr[rand_int1 : rand_int2]

	if(len(row) != 0 and len(row) % 2 == 0):
		output.append(row)

	

for row in output:
	for num in row:
		print num,
	print















