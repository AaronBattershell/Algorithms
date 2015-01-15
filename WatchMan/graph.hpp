#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <map>
#include <list>

template <typename T>
struct Vertex {
	Vertex(T v)
		: value(v) { }
	
	T value;

	bool operator==(const Vertex<T> &other) const {
		return this->value == other.value;
  	}

  	//required for inheriting from map
  	bool operator<(const Vertex<T> &other) const {
		return this->value < other.value;
  	}
};

template <typename T>
struct Edge {
	Edge(Vertex<T> v, int w) 
		: vertex(v), weight(w) { }

	Vertex<T> vertex;

	int weight;
	int capacity() { return weight; }
};

template <typename T>
struct AdjacencyList : std::list< Edge<T> > {

};

template <typename T>
struct Graph : std::map< Vertex<T>, AdjacencyList<T> > {
	//You can assume all the basic functions from map

	//function to add an edge
	void add_edge(Vertex<T> src, Vertex<T> dest, int capacity) {
		//check that the vertex isnt already in the graph
		//if its not
		if(this->find(src) == this->end()) {
			//add it to the graph
			//add the dest to its adjacency list
			Edge<T> e(dest, capacity);
			AdjacencyList<T> al;
			al.push_back(e);
			this->emplace(src, al);
		}
		//if it is already in the graph then add the dest to its adjacency list
		else {
			//get the pair
			auto vertex = this->find(src);
			//add the edge to the adjacency list
			Edge<T> e(dest, capacity);
			vertex->second.push_back(e);
		}
	}

	void print() {
		for(auto v : *this) {
			std::cout << '|' << v.first.value << "| -> ";
			for(auto e : v.second) {
				std::cout << e.vertex.value << '(' << e.capacity() << ") ->";
			}
			std::cout << '\n';
		}
	};
};

#endif