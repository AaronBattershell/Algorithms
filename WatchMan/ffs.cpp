#include "ffs.hpp"


//given a path, get the mininmum edge capacity along that path
int min_capacity(std::vector< Vertex<int>* > path) {
	
	int min = 0;
	//if the path is empty then there was no path
	//immediately return 0
	if(path.empty())
		return min;
	//we know a path must have at least two nodes
	//the src and the sink must be in the path
	//we look at the weight of the edge connecting the first two nodes
	//set the value of the minimum edge to that weight
	//we know the first node never has a predecessor edge
	//look at the second node for its pred edge
	if(path.at(1)) {
		//if the pred edge is not null which it never should be
		if(path.at(1)->pred)
			min = path.at(1)->pred->capacity();
		else
			std::cout << "HUGE ERROR IN MIN CAPAC\n";
	}
	else
		return 0; // error return 0
	
	for(auto vertex : path) {
		if(vertex->pred)
			if(vertex->pred->capacity() < min)
				min = vertex->pred->capacity();
	}
	return min;
}

Graph<int> construct_residual_graph(Graph<int> &g) {
	Graph<int> rGraph;
	for(auto pair : g) {
		Vertex<int> vertex = pair.first;
		AdjacencyList<int> al = pair.second;
		rGraph.add_vertex(&vertex);
		for(auto edge : al) {
		}
	}
	
}


//takes a network, src, and sink and performs ford fulkerson on the graph
// returns an int which is the max flow of the network
int ford_fulkerson(Graph<int> &g, Vertex<int>* src, Vertex<int>* sink) {
	std::vector< Vertex<int>* > path = bfs(g, src, sink);
	//find the shortest path (in terms of number of edges)
	while(path.size() < 2) {
		//path cannot be empty
		//it must have at least two nodes (src and sink)
		//get the min capacity going along a path
		int min_cap = min_capacity(path);
	
		//min capacity cannot be zero at this point otherwise there is no path
		if(min_cap == 0)
			return 0;
		
		//adjust the flow going along each edge based on the min_cap
		for(auto vertex : path) {
			if(vertex->pred)
				vertex->pred->active_flow = min_cap;
		}
		
		//create a residual graph
	}	
	return 0;
}
