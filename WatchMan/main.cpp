#include "graph.hpp"
#include "bfs.hpp"
#include "intersection.hpp"
#include "parsing.hpp"
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	//some aliases
	using Vint = Vertex<int>;
	using Eint = Edge<int>;
	using al = AdjacencyList<Eint>;

	VertexFactory<int>* vf = new VertexFactory<int>();
	Graph<int> g;

	//read the option. can be -b(bfs), -f(ford-folkerson), -m (museum)
	std::string opt;

	opt = argv[1]; //option

	// TODO: better input validation in parameters
	// ACTUALLY PARSE THE FILES
	if(opt == "-b") {
		//check arg count
		if(argc != 5) {
			std::cout << "Not enough parameters given.\n";
			std::cout << "Found " << argc << " parameters. Need " << 5 << " parameters.\n";
			return -1;
		}

		std::cout << "You have chosen BFS with file " << argv[2]
				  << ". Finding path from " << argv[3] << " to " << argv[4] 
				  << '\n';

		// testing vertex factory is return old pointers above
		Vint* src = vf->make_vertex( atoi(argv[3]) );
		Vint* dest = vf->make_vertex( atoi(argv[4]) );
		std::cout << "===File Contents===\n";
		g = parse_bfs(argv[2], vf);
		std::cout << "===Graph Adjacency List===\n";
		g.print();
		std::cout << "===PATH===\n";
		auto path = bfs(g, src, dest);
	}
	else if(opt == "-f") {
		std::cout << "You have chosen Ford-Fulkerson with file " << argv[2] << '\n';
	}
	else if(opt == "-m") {
		std::cout << "You have chosen Museum Problem with file " << argv[2] << '\n';
	}

	delete vf;

	// Intersection Testing
	//arc a(point(0, 1), point(1, 2), 0, -1);
	//line b(point(-10, 1.5), point(10, 1.5));
	//cout << a.intersect(b); 

	return 0;
}
