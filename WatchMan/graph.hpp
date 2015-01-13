#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

template <class T>
struct AdjListNode {
	AdjListNode(T v, int w) 
		: v(v), weight(w) { }

	T v;
	int weight;

	T value() { return v; }
	int capacity() { return weight; }
};

template <class T>
struct AdjacencyList {
	AdjacencyList(AdjListNode<T> h)
		: head(h) { } 

	AdjListNode<T> head;

	std::vector< AdjListNode<T> > n;
	std::vector< AdjListNode<T> > neighbors() { return n; }	
};

template <class T>
struct Graph {
	void add_edge(AdjListNode<T> src, AdjListNode<T> dest);
	// number of vertices
	int V;
	std::vector< AdjacencyList<T> > lists;
};

#endif