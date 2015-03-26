/*
/ Output: A file with 1 <= [DATA_POINTS] points where each point consists of
/   1 <= [DIMENSION] dimensions. Each point's coordinates will be on one line.
/   Each dimension of a point will vary by a random percentage of
/   0 <= [VARIANCE_RANGE]. All data points increase linearly such that if
/   point 1 is (1, 1, ..., 1), point 2 would be (2, 2, ..., 2). In this 
/   implementation, each point has a positive offset of [VARIANCE_RANGE] to
/   avoid potential negaitive numbers.
/
/ Expected CLI Input: [DATA_POINTS] [DIMENSIONS] [VARIANCE_RANGE] [OUTPUT_FILE_NAME]
/
/ How to compile: g++ PointGenerator.cpp -o PG.out
/
/ Sample arguments for running: ./PG.out 100 3 10 Output.txt
*/

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
	if (argc != 5) {
		cout << "Unexpected number of arguments." << endl
		     << "Expected: [DATA_POINTS] [DIMENSIONS] [VARIANCE_RANGE] [OUTPUT_FILE_NAME]" << endl;

		return 0;
	}

	try {
		srand(time(0));
		
		int dataPoints = atoi(argv[1]);
		int dimensions = atoi(argv[2]);
		int varianceRange = atoi(argv[3]);

		fstream out(argv[4], fstream::out);

		out << dataPoints << ' ' << dimensions << endl;

		for (int points = 1; points <= dataPoints; ++points) {
			for (int dimmension = 0; dimmension < dimensions; ++dimmension) {
				out << setw(10) << left << points + varianceRange + varianceRange * ((rand() % 101) / 100.0) * (rand() % 2 ? 1 : -1) << ' ';
			}
			out << endl;
		}

		cout << "Output written to " << string(argv[4]) << endl;
	}
	catch (exception e) {
		cout << "An unexpected error has occured. Verify that CLI arguments are in order." << endl;
	}

	return 0;
}
