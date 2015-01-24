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
	VertexFactory<int>* vf = rGraph.vf;

	for(auto pair : g) {
		Vertex<int>* src = vf->make_vertex(pair.first.value);
		AdjacencyList<int> al = pair.second;
		for(auto edge : al) {
			//add a new forward and backward edge for each
			//vertex in the adjacency list
			Vertex<int>* dest = vf->make_vertex(edge->dest->value); 
			int fWeight = edge->residual_capacity(); //forward flow
			int bWeight = edge->active_capacity();  //backwards flow
	
			if(fWeight > 0)
				rGraph.add_edge(src, dest, fWeight);
			//check that the active capacity > 0 so we dont add a backwards
			//edge with a weight of 0
			if(bWeight > 0)
				rGraph.add_edge(dest, src, bWeight);
		}
	}
	return rGraph;
}


//takes a network, src, and sink and performs ford fulkerson on the graph
// returns an int which is the max flow of the network
int ford_fulkerson(Graph<int> &g, Vertex<int>* src, Vertex<int>* sink) {
	std::vector< Vertex<int>* > path = bfs(g, src, sink);
	Graph<int> graph = g;
	//find the shortest path (in terms of number of edges)
	while(path.size() > 2) {
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

		std::cout << "===Augmented Network===\n";
		graph.print();
		//create a residual graph
		std::cout << "===Residual Network===\n";
		Graph<int> rGraph = construct_residual_graph(graph);
		rGraph.print();
		
		path = bfs(rGraph, 
				   rGraph.vf->make_vertex(src->value),
				   rGraph.vf->make_vertex(sink->value));

		graph = rGraph;
	}	
	return 0;
}

Vertex<int> get_src(Graph<int> &g) {

	std::set< Vertex<int> > V; //vertices
	for(auto pair : g) {
		V.insert(pair.first);
	}
	for(auto pair : g) {
		//iterate through the adjacency list of each node
		for(auto edge : pair.second) {
			//if there is an edge directed towards a node
			//we know it is not a src
			//erase it from the set V
			if(auto dest = edge->dest)
				V.erase(*dest);
		}
	}

	//once we're done V should contain only src nodes
	if(V.size() == 1) {
		std::cout << (*V.begin()).value << '\n';
		return *V.begin();
	}
	else if(V.empty()) {
		std::cout << "WARNING : ERROR : "
		          << "Graph has no sources. Cannot perform Ford-Fulkerson.\n";
		Vertex<int> v(-100000001);
		return v;
	}
	else {
		std::cout << "Multiple sources. Forming super source. \n";
	}
}


Vertex<int> get_sink(Graph<int> &g) {
	//find the sink in a graph
	//if the graph has more than one sink form a supersink
	// Note: a sink by definition is a vertex with no adjacent vertices
	std::vector< Vertex<int> > sinks;
	for(auto pair : g) {
		if(pair.second.empty()) {
			sinks.push_back(pair.first);
		}
	}
	if(sinks.size() == 1) {
		std::cout << (*sinks.begin()).value << '\n';
		return *sinks.begin();
	}
	else if(sinks.empty()) {
		std::cout << "WARNING : ERROR : "
		          << "Graph has no sinks. Cannot perform Ford-Fulkerson.\n";
		Vertex<int> v(-100000000);
		return v;
	}
	else {
		std::cout << "Multiple sinks. Forming super sink. \n";
	}
}