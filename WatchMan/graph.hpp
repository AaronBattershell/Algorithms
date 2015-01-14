#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

template <typename T>
struct Vertex {
	Vertex(T v)
		: v(v) { }
	T v;

	T value() { return v; }
	bool operator==(const Vertex<T> &other) const {
		return this.v == other.v;
  	}
};

template <typename T>
struct Edge {
	Edge(Vertex<T> v, int w) 
		: v(v), weight(w) { }

	Edge(Vertex<T> v)
		: v(v), weight(0) { }

	Vertex<T> v;
	int weight;

	Vertex<T> vertex() { return v; }
	int capacity() { return weight; }
};

template <typename T>
struct AdjacencyList {
	AdjacencyList(Vertex<T> h)
		: head(h) { } 

	Vertex<T> head;

	std::vector< Edge<T>* > n;
	std::vector< Edge<T>* > neighbors() { return n; }	
};

template <typename T>
struct Graph {
	Graph(std::vector< AdjacencyList<T> > vertices) 
		: vertices(vertices), num_vert(vertices.size()) { }

	bool contains(Vertex<T> vertex);
	AdjacencyList<T>* find(Vertex<T> vertex);
	void add_edge(Vertex<T> src, Vertex<T> dest, int capacity);
	// number of vertices
	int num_vert;
	std::vector< AdjacencyList<T> > vertices;
};

#endif