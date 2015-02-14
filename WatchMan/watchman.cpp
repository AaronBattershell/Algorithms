#include "watchman.hpp"
using namespace std;

watchman::watchman(string inFileName, string outFileName)
	:input(inFileName), out(outFileName, fstream::out) { 

	cout << "Output written to " << outFileName << endl;
}

void watchman::solve() {
	for (int iter = 1; input.get_next_problem(); ++iter) {	
		vector<line> straitWall;
		vector<arc> curveWall;
		Graph<int> g;

		createWalls(straitWall, curveWall);
		findSightLines(straitWall, curveWall, g);
		
		Vertex<int> *src = g.vf->make_vertex(get_src(g).value);
		Vertex<int> *sink = g.vf->make_vertex(get_sink(g).value);

		printReuslt(ford_fulkerson(g, src, sink), iter);

		delete g.vf;
	}	
}	

void watchman::createWalls(vector<line> &straitWall, vector<arc> &curveWall) {
	for (int i = 0; i < input.wall_setVector.size(); ++i) {
		for (int n = 0; n < input.wall_setVector[i].size(); ++n) {
			if (input.wall_setVector[i][n].size() == 2) { 
				// Adding a wall
				straitWall.push_back(line(
					point(input.wall_setVector[i][n][0], input.wall_setVector[i][n][1]), 
					point(input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][0], 
						input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][1])));
			}
			else { 
				// Adding an arc
				curveWall.push_back(arc(
					point(input.wall_setVector[i][n][0], input.wall_setVector[i][n][1]), 
					point(input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][0], 
						input.wall_setVector[i][(n + 1) % input.wall_setVector[i].size()][1]), 
						input.wall_setVector[i][n][2], input.wall_setVector[i][n][3]));		
			}
		}
	}
}

void watchman::findSightLines(vector<line> &straitWall, vector<arc> &curveWall, Graph<int> &g) {
	using Vint = Vertex<int>;

	Vint *superSource = g.vf->make_vertex(-1);
	Vint *superSink = g.vf->make_vertex(-2);

	for (int i = 0; i < input.guard_setVector.size(); ++i) {
		for (int n = 0; n < input.paint_setVector.size(); ++n) {
			line lineOfSight(point(input.guard_setVector[i][0], input.guard_setVector[i][1]),
				point(input.paint_setVector[n][0], input.paint_setVector[n][1]));
			
			Vint *curr = g.vf->make_vertex(i);
	
			if (clearLineOfSight(lineOfSight, straitWall, curveWall)) {
				Vint *dest = g.vf->make_vertex(n + input.guard_setVector.size());
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

void watchman::printReuslt(Graph<int> g, int iter) {
	int neededArt = 0;
	int watchedArt = 0;
	
	// Find the sum of the watch number of all paintings
	for (int i = 0 ; i < input.paint_setVector.size(); ++i) {
		neededArt += input.paint_setVector[i][2];
	}

	Vertex<int>* sink = g.vf->make_vertex(get_sink(g).value);

	watchedArt = get_max_flow(g, sink);
	
	//cout << "Case " << iter << ": " << (neededArt == watchedArt ? "Yes" : "No") << endl;
	out << "Case " << iter << ": " << (neededArt == watchedArt ? "Yes" : "No") << endl;
	
	// Provided a good case has been found, print out which guards watched which painting
	if (neededArt == watchedArt) {
		int i = -2;
		for(auto v : g) {
			++i;
			if (!(i > 0 && i <= input.guard_setVector.size())) {
				continue;
			}

			string output("\tG" + to_string(v.first.value + 1) + ":");

			for(auto e : v.second) {
				if (e->active_capacity()) {					
					output += "A" + to_string(e->dest->value + 1 - input.guard_setVector.size()) + ',';
				}
			}

			//cout << output.substr(0, output.size()-1) + '\n';
			out << output.substr(0, output.size()-1) + '\n';
		}
	}
}












