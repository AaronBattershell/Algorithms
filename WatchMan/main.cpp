#include "graph.hpp"
#include "bfs.hpp"
#include "intersection.hpp"
#include "parsing.hpp"
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	VertexFactory<int>* vf = new VertexFactory<int>();
	Graph<int> g;

	//read the option. can be -b(bfs), -f(ford-folkerson), -m (museum)
	std::string opt;
	if(argc < 3) {
		std::cout << "Not enough parameters given.\n";
		return -1;
	}

	opt = argv[1]; //option

	// TODO: better input validation in parameters
	// ACTUALLY PARSE THE FILES
	if(opt == "-b") {
		std::cout << "You have chosen BFS with file " << argv[2] << '\n';
		std::cout << "===File Contents===\n";
		g = parse_bfs(argv[2], vf);
	}
	else if(opt == "-f") {
		std::cout << "You have chosen Ford-Fulkerson with file " << argv[2] << '\n';
	}
	else if(opt == "-m") {
		std::cout << "You have chosen Museum Problem with file " << argv[2] << '\n';
	}

	using Vint = Vertex<int>;
	using Eint = Edge<int>;
	using al = AdjacencyList<Eint>;

	Vint* a = vf->make_vertex(0);
	Vint* b = vf->make_vertex(1);
	Vint* c = vf->make_vertex(2);
	Vint* d = vf->make_vertex(3);

	// testing vertex factory is return old pointers above
	Vint* a1 = vf->make_vertex(0);
	Vint* d1 = vf->make_vertex(3);

	//replicate the same graph as in the example on the assignment sheet

	std::cout << "===Graph Adjacency List===\n";
	g.print();

	std::cout << "===PATH===\n";
	auto path = bfs(g, a1, d1);

	delete vf;

	// Intersection Testing
	//arc a(point(0, 1), point(1, 2), 0, -1);
	//line b(point(-10, 1.5), point(10, 1.5));
	//cout << a.intersect(b); 

	return 0;
}
