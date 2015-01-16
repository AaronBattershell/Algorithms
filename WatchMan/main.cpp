#include "graph.hpp"
#include "bfs.hpp"
#include "intersection.hpp"
#include <string>
#include <unordered_set>

using namespace std;

int main() {
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
	g.add_edge(a, d, 2);
	g.add_edge(a, b, 3);
	g.add_edge(a, c, 6);
	g.add_edge(b, c, 2);

	g.print();

	std::cout << "PATH\n";
	auto path = bfs(g, b, d);

	return 0;
}