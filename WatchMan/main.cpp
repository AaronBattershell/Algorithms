#include "graph.hpp"
#include "bfs.hpp"
#include "intersection.hpp"
#include <string>

using namespace std;

int main() {
	using Vint = Vertex<int>;
	using Eint = Edge<int>;
	using al = AdjacencyList<Eint>;

	Vint a(0);
	Vint b(1);
	Vint c(2);
	Vint d(3);

	//replicate the same graph as in the example on the assignment sheet
	Graph<int> g;
	g.add_edge(a, b, 3);
	g.add_edge(a, c, 6);
	g.add_edge(b, c, 2);
	g.add_edge(a, d, 8);
	g.add_edge(c, d, 1);

	g.print();
	
	

	// Sample line intersection demonstration
	line line1(point(0, 0), point(10, 10));
	line line2(point(0, 10), point(9.99, 10));
	cout << endl << line1.intersect(line2) << endl;

	return 0;
}
