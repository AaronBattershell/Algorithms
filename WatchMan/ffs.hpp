#include "graph.hpp"
#include "bfs.hpp"

//performs ford-fulkerson on one src and one sink
Graph<int> ford_fulkerson(Graph<int> g, Vertex<int>* src, Vertex<int>* sink);
Graph<int> ford_fulkerson_detailed(Graph<int> g, Vertex<int>* src, Vertex<int>* sink);

//given a graph g, get the src nodes for it
//if more than one src node, form a super src
Vertex<int> get_src(Graph<int> &g);

//given a graph g, get the sink nodes for it
Vertex<int> get_sink(Graph<int> &g);

// returns the vertices in the min cut given a residual graph
std::vector< Vertex<int>* > min_cut(Graph<int> &rGraph);

int get_max_flow(Graph<int> &g, Vertex<int>* sink);

