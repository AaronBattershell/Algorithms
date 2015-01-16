#ifndef BFS_HPP
#define BFS_HPP

#include "graph.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cassert>

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

}// namespace

// s = src
// v = destination
template <typename T>
void print_path(Graph<T> graph, Vertex<T>* s, Vertex<T>* v) {
	if(*s == *v)
		std::cout << s->value;
	else if(v->pred == nullptr)
		std::cout << "No path found\n";
	else {
		print_path(graph, s, v->pred);
		std::cout << "->" << v->value;
	}
	std::cout << '\n';
}

//Algorithm taken from Intro to Algorithms 3e by Cormen, Lesierson, and Rivest
template <typename T>
std::vector< Vertex<T> > bfs(Graph<T> graph, Vertex<T>* src, Vertex<T>* dest) {
	std::cout << "==BFS==\n";
	using V = Vertex<T>;

	std::queue<V*> q; //empty queue

	src->color = GRAY;
	src->d = 0;
	q.push(src);

	while(!q.empty()) {
		V* u = q.front();
		q.pop();

		auto adj_u = graph.get_adjacent_list(*u);
		for(auto edge : adj_u) {
			if(edge.vertex->color == WHITE) {
				edge.vertex->color = GRAY;
				edge.vertex->d = u->d + 1;
				edge.vertex->pred = u;
				q.push(edge.vertex);
			}
		}
		u->color = BLACK;
	}
	
	print_path(graph, src, dest);

	// ordered_set<V> visited;
	// std::queue<V> q;
	// q.push(src);

	// while(!q.empty()) {
	// 	V current = q.front();
	// 	visited.add(current);
	// 	q.pop();
	// 	// std::cout << "CURRENt: " << current.value << '\n';
	// 	//if we found the node we're looking for then return
	// 	if(current == dest) {
	// 		// std::cout << "FOUND: " << current.value << '\n';
	// 		return visited.set();
	// 	}
	// 	//else look at the adjacent nodes
	// 	auto adj_list = graph.get_adjacent_list(current);
	// 	for(auto edge : adj_list) {
	// 		if(!visited.contains(edge.vertex)) {
	// 			// std::cout << "ENQ: " << edge.vertex.value << '\n';
	// 			q.push(edge.vertex);
	// 		}
	// 	}
	// }
	//if not found return empty
	std::vector<V> empty;
	return empty;
}

#endif