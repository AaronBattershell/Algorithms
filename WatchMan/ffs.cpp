#include "ffs.hpp"

namespace {

template <typename T>
struct ordered_set {
	std::set<T> s;
	std::vector<T> v;
	// inserts into the vector iff you can insert into the set
	bool add(T elem) {
		auto res = s.insert(elem);
		if(res.second) {
			v.push_back(elem);
			return true;
		}
		if(!res.second) {
			return false;
		}
	}

	//returns true iff contains the elem
	bool contains(T elem) {
		auto search = s.find(elem);
		if(search != s.end())
			return true;
		else
			return false;
	}

	std::vector<T> set() { return v; } 
};

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

//takes the original graph and the residual graph
//augments the original path using the residual graph
void augment_path(Graph<int> &g, std::vector< Vertex<int>* > rPath) {
	//once we've found a path in the rGraph, we need to change
	//the path in the main graph
	//for each edge in the graph
	for(auto rVertex : rPath) {
		//check for nullptr on pred
		if(Edge<int>* rPred = rVertex->pred) {
			//find the edge in the original graph
			Edge<int>* edge = g.get_edge(*(rPred->src), *(rPred->dest));

			//if the search returns a result (not nullptr)
			if(edge) {
				//if we find the forward edge
				//add the active flow of the residual path edge
				//to the original graph
				edge->active_flow += rPred->active_flow;
			}
			//if search returns nullptr we know its a backwards edge
			//search again with the dest and src switched
			else {
				edge = g.get_edge(*(rPred->dest), *(rPred->src));
				//if we know its a backwards edge
				if(edge) {
					//subtract the active flow of the residual path edge
					// from th edge in the original graph
					edge->active_flow -= rPred->active_flow;
				}
			}
		}
	}
}

Graph<int> push_flow(Graph<int> &g, Vertex<int>* src, Vertex<int>* sink) {
	
	std::vector< Vertex<int>* > path = bfs(g, src, sink);
	int min_cap = min_capacity(path);
	for(auto vertex : path) {
		if(vertex->pred)
			vertex->pred->active_flow = min_cap;
	}

	return g;
}

int get_min_cut(Graph<int> &graph, 
				Graph<int> &rGraph, 
				Vertex<int>* src, 
				Vertex<int>* dest) 
{
	using V = Vertex<int>;
	//perform depth first search starting from src to sink
	ordered_set< Vertex<int> > visited;
	
	std::queue<V> q;
	q.push(*src);
	while(!q.empty()) {
		V current = q.front();
		visited.add(current);
		q.pop();
		//if we found the node we're looking for then return
		if(current == *dest) {
			break;
		}
		//else look at the adjacent nodes
		auto adj_list = rGraph.get_adjacent_list(current);
		for(auto edge : adj_list) {
			if(!visited.contains(*(edge->dest))) {
				q.push(*edge->dest);
			}
		}
	}

	std::cout << "===Min Cut===\n";
	std::cout << "Vertices in S: ";

	std::set< Vertex<int> > tempS;

	for(auto v : visited.set()) {
		tempS.insert(v);
	}

	for(auto v : tempS) {
		std::cout << v.value << " ";
	}
	std::cout << '\n';

	std::set< Edge<int>* > S;
	
	//iterate over all the edges inside the graph
	for(auto edge : *graph.ef) {
		for(auto vs : tempS) {
			//if the src of the edge is part of S
			// and the dest is not part of S (so part of T)
			if(*(edge->src) == vs && (tempS.find(*(edge->dest)) == tempS.end())) {
				S.insert(edge);
			}
		} 
	}

	int min_cut = 0;
	std::cout << '\n';
	for(auto e : S) {
		if(e->src != nullptr && e->dest != nullptr) {
			std::cout << e->src->value << "-(" << e->weight <<  ")->" << e->dest->value << '\n';
			min_cut += e->weight;
		}
	}

	return min_cut;
}



} //namespace


int get_max_flow(Graph<int> &g, Vertex<int>* sink) {
	//iterate over all the edges
	//find all edges where the destination is the sink
	//sum up all the active flows
	int max_flow = 0;
	for(auto e : *(g.ef)) {
		if(*(e->dest) == *sink) {
			max_flow += e->active_capacity();
		}
	}
	return max_flow;
}

//takes a network, src, and sink and performs ford fulkerson on the graph
// returns an int which is the max flow of the network
//this version prints out a bunch of details about the algorithm as it works
Graph<int> ford_fulkerson_detailed(Graph<int> g, Vertex<int>* src, Vertex<int>* sink) {
	
	//construct a residual graph thats initially the same as the original
	Graph<int> rGraph = rGraph.deep_copy(g);
	Vertex<int>* rSrc = rGraph.vf->make_vertex(get_src(rGraph).value);
	Vertex<int>* rSink = rGraph.vf->make_vertex(get_sink(rGraph).value);

	std::vector< Vertex<int>* > path = bfs(rGraph, rSrc, rSink);

	//find the shortest path (in terms of number of edges)
	while(path.size() >= 2) {
		//path cannot be empty
		//it must have at least two nodes (src and sink)
		//get the min capacity going along a path
		int min_cap = min_capacity(path);
	
		//min capacity cannot be zero at this point otherwise there is no path
		if(min_cap == 0)
			return g;
		
		//adjust the flow going along each edge based on the min_cap
		for(auto vertex : path) {
			if(vertex->pred)
				vertex->pred->active_flow = min_cap;
		}

		//augment the original graph
		std::cout << "===Augmented Path===\n";
		augment_path(g, path);
		g.print();
		
		//create a residual graph
		std::cout << "===Residual Network===\n";
		rGraph = construct_residual_graph(g);
		rGraph.print();
		
		path = bfs(rGraph, 
				   rGraph.vf->make_vertex(src->value),
				   rGraph.vf->make_vertex(sink->value));
	}

	//get the min cut from the residual graph
	int min_cut = get_min_cut(g, rGraph, src, sink);
	std::cout << "Min cut= " << min_cut << '\n';
	//get the max flow from the residual graph
	int max_flow = get_max_flow(g, sink);
	std::cout << "Max flow= " << max_flow << '\n';

	return g;
}


//takes a network, src, and sink and performs ford fulkerson on the graph
// returns an int which is the max flow of the network
Graph<int> ford_fulkerson(Graph<int> g, Vertex<int>* src, Vertex<int>* sink) {
	
	//construct a residual graph thats initially the same as the original
	Graph<int> rGraph = rGraph.deep_copy(g);
	Vertex<int>* rSrc = rGraph.vf->make_vertex(get_src(rGraph).value);
	Vertex<int>* rSink = rGraph.vf->make_vertex(get_sink(rGraph).value);

	std::vector< Vertex<int>* > path = bfs(rGraph, rSrc, rSink);

	//find the shortest path (in terms of number of edges)
	while(path.size() >= 2) {
		//path cannot be empty
		//it must have at least two nodes (src and sink)
		//get the min capacity going along a path
		int min_cap = min_capacity(path);
	
		//min capacity cannot be zero at this point otherwise there is no path
		if(min_cap == 0)
			return g;
		
		//adjust the flow going along each edge based on the min_cap
		for(auto vertex : path) {
			if(vertex->pred)
				vertex->pred->active_flow = min_cap;
		}

		//augment the original graph
		//std::cout << "===Augmented Path===\n";
		augment_path(g, path);
		//g.print();
		
		//create a residual graph
		//std::cout << "===Residual Network===\n";
		rGraph = construct_residual_graph(g);
		//rGraph.print();
		
		path = bfs(rGraph, 
				   rGraph.vf->make_vertex(src->value),
				   rGraph.vf->make_vertex(sink->value));
	}

	//get the min cut from the residual graph
	//int min_cut = get_min_cut(g, rGraph, src, sink);
	//std::cout << "Min cut= " << min_cut << '\n';
	//get the max flow from the residual graph
	//int max_flow = get_max_flow(g, sink);
	//std::cout << "Max flow= " << max_flow << '\n';

	return g;
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

		// Assigne all source nodes a super source
		Vertex<int> *super_source = g.vf->make_vertex(-1);
		for (auto i : V) {
			Vertex<int>* temp_v = g.get_vertex(i.value);
			g.add_edge(super_source, temp_v, 10000001);	
		}

		return *super_source;
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

		// Assigne all sinks a super sink
		Vertex<int> *super_sink = g.vf->make_vertex(-2);
		for (auto i : sinks) {
			Vertex<int>* temp_v = g.get_vertex(i.value);
			g.add_edge(temp_v, super_sink, 10000001);	
		}

		return *super_sink;
	}
}
