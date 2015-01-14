#include "graph.hpp"

template <typename T>
bool Graph<T>::contains(Vertex<T> vertex) {
	for(auto v : this.vertices) {
		if(v.head == vertex)
			return true;
	}
	return false;
}

template <typename T>
AdjacencyList<T>* Graph<T>::find(Vertex<T> vertex) {
	for(auto v : this.vertices) {
		if(v.head == vertex)
			return &v;
	}
	return nullptr;
}

template <typename T>
void Graph<T>::add_edge(Vertex<T> src, Vertex<T> dest, int capacity) {
	AdjacencyList<T> l(src);
	if(this.contains(src)) {

	}
}