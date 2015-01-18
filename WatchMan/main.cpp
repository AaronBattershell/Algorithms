#include "graph.hpp"
#include "bfs.hpp"
#include "intersection.hpp"
#include "parsing.hpp"
#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {

	//read the option. can be -b(bfs), -f(ford-folkerson), -m (museum)
	std::string opt;
	if(argc < 3) {
		std::cout << "Not enough parameters given.\n";
		return -1;
	}

	opt = argv[1];

	// TODO: better input validation in parameters
	// ACTUALLY PARSE THE FILES
	if(opt == "-b") {
		std::cout << "You have chosen BFS with file " << argv[2] << '\n';
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

	Vint* a = new Vint(0);
	Vint* a1 = new Vint(0);
	Vint* b = new Vint(1);
	Vint* c = new Vint(2);
	Vint* d = new Vint(3);

	//replicate the same graph as in the example on the assignment sheet
	Graph<int> g;

	g.add_edge(a, d, 8);
	g.add_edge(a, b, 3);
	g.add_edge(a, c, 6);
	g.add_edge(b, c, 2);
	g.add_edge(c, d, 1);


	g.print();

	std::cout << "PATH\n";
	auto path = bfs(g, a, d);

	return 0;
}