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
		Graph<int> g;
		VertexFactory<int>* vf = g.vf;

		createWalls(straitWall, curveWall);
		findSightLines(straitWall, curveWall, g, vf);
	}
}	

void watchman::createWalls(vector<line> &straitWall, vector<arc> &curveWall) {
	for (int i = 0; i < input.wall_setVector.size(); ++i) {
		for (int n = 0; n < input.wall_setVector[i].size(); ++n) {
			if (input.wall_setVector[i][n].size() == 2) { // Adding a wall
				straitWall.push_back(line(
					point(input.wall_setVector[i][n][0], input.wall_setVector[i][n][1]), 
					point(input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][0], 
						input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][1])));
			}
			else { // Adding an arc
				curveWall.push_back(arc(
					point(input.wall_setVector[i][n][0], input.wall_setVector[i][n][1]), 
					point(input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][0], 
						input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][1]), 
						input.wall_setVector[i][n][2], input.wall_setVector[i][n][3]));		
			}
		}
	}	
}

void watchman::findSightLines(vector<line> &straitWall, vector<arc> &curveWall, Graph<int> &g, VertexFactory<int> *vf) {

}
