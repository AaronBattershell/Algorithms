Taken from PointGenerator.cpp
	Output: A file with 1 <= [DATA_POINTS] points where each point consists of
	  1 <= [DIMENSION] dimensions. Each point's coordinates will be on one line.
	  Each dimension of a point will vary by a random percentage of
	  0 <= [VARIANCE_RANGE]. All data points increase linearly such that if
	  point 1 is (1, 1, ..., 1), point 2 would be (2, 2, ..., 2). In this 
	  implementation, each point has a positive offset of [VARIANCE_RANGE] to
	  avoid potential negaitive numbers.

	Expected CLI Input: [DATA_POINTS] [DIMENSIONS] [VARIANCE_RANGE] [OUTPUT_FILE_NAME]

	How to compile: g++ PointGenerator.cpp -o PG.out

	Sample arguments for running: ./PG.out 100 3 10 Output.txt
	
Other
	For the SAT files each states scores are listed from 1990 - 2004 left to right.
	Source: http://mathforum.org/workshops/sum96/data.collections/datalibrary/data.set6.html