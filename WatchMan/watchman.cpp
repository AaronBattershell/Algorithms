#include "watchman.hpp"
using namespace std;

watchman::watchman(string fileName)
	:input(fileName) 
{ }

void watchman::solve() {
	for (int iter = 1; input.get_next_problem(); ++iter) {	
		int artSum = 0;
		vector<line> straitWall;
		vector<arc> curveWall;
		Graph<int> g;
		VertexFactory<int>* vf = g.vf;

		for (int i = 0 ; i < input.paint_setVector.size(); ++i) {
			artSum += input.paint_setVector[i][2];
		}

		createWalls(straitWall, curveWall);
		findSightLines(straitWall, curveWall, g, vf);
		
		Vertex<int> *src = vf->make_vertex(get_src(g).value);
		Vertex<int> *sink = vf->make_vertex(get_sink(g).value);

		cout << "===Starting Graph===\n";
		cout << "(-1 super sorce, -2 super sink, node 0 - " << input.guard_setVector.size() - 1;
		cout << " gaurds, nodes " << input.guard_setVector.size() << " - ";
		cout << input.guard_setVector.size() + input.paint_setVector.size() - 1 << " paintings" << endl;
		g.print();
		
		ford_fulkerson(g, src, sink);


		delete vf;
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
	using Vint = Vertex<int>;

	Vint *superSource = vf->make_vertex(-1);
	Vint *superSink = vf->make_vertex(-2);

	for (int i = 0; i < input.guard_setVector.size(); ++i) {
		for (int n = 0; n < input.paint_setVector.size(); ++n) {
			line lineOfSight(point(input.guard_setVector[i][0], input.guard_setVector[i][1]),
				point(input.paint_setVector[n][0], input.paint_setVector[n][1]));
			
			Vint *curr = vf->make_vertex(i);
	
			if (clearLineOfSight(lineOfSight, straitWall, curveWall)) {
				Vint *dest = vf->make_vertex(n + input.guard_setVector.size());
				g.add_edge(curr, dest, 1);
				g.add_edge(superSource, curr, input.guard_setVector[i][2]);
				g.add_edge(dest, superSink, input.paint_setVector[n][2]); 
			}
		}
	}
}

bool watchman::clearLineOfSight(line view, std::vector<line> &straitWall, std::vector<arc> &curveWall) {
	for (int i = 0; i < straitWall.size(); ++i) {
		if (view.intersect(straitWall[i])) {
			return false;
		}	
	}

	for (int i = 0; i < curveWall.size(); ++i) {
		if (view.intersect(curveWall[i])) {
			return false;
		}
	}

	return true;
}












