#include <set>
#include "graph.hpp"
#include "bfs.hpp"

//performs ford-fulkerson on one src and one sink
int ford_fulkerson(Graph<int> &g, Vertex<int>* src, Vertex<int>* sink);

//get the min capacity in a path
int min_capacity(std::vector< Vertex<int>* > path);

//if a network has more than one src, add a super source to the graph
//input is a graph representing a network and a set of srcs
void super_source(Graph<int> &g, std::vector< Vertex<int>* > srcs);

//if a network has more than one sink, add a super sink to the graph
//input is a graph representing a network and a set of sinks
void super_sink(Graph<int> &g, std::vector< Vertex<int>* > sinks);

//given a graph g, get the src nodes for it
//if more than one src node, form a super src
Vertex<int> get_src(Graph<int> &g);

//given a graph g, get the sink nodes for it
Vertex<int> get_sink(Graph<int> &g);

