#include "watchman.hpp"
using namespace std;

watchman::watchman(string fileName)
	:input(fileName) {
	
}

void watchman::solve() {
	for (int iter = 1; input.get_next_problem(); ++iter) {	
		//input.print_wallSet(input.wall_setVector);
    		//input.print_paintSet(input.paint_setVector);
    		//input.print_guardSet(input.guard_setVector);

		vector<line> straitWall;
		vector<arc> curveWall;

		createWalls(straitWall, curveWall);
		findSightLines(straitWall, curveWall);
	}
}	

void watchman::createWalls(vector<line> &straitWall, vector<arc> &curveWall) {
	/*for (int i = 0; i < input.wall_setVector.size(); ++i) {
		for (int n = 0; n < input.wall_setVector[i].size(); ++n) {
			for (int j = 0; j < input.wall_setVector[i][n].size(); ++j) {
				cout << input.wall_setVector[i][n][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}*/
}

void watchman::findSightLines(vector<line> &straitWall, vector<arc> &curveWall) {

}
