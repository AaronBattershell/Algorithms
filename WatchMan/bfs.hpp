#ifndef BFS_HPP
#define BFS_HPP

#include "graph.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cassert>
#include <algorithm>

namespace {

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
		std::cout << "-(" << v->pred->weight << ")-> " << v->value;
	}
	std::cout << '\n';
}

template <typename T>
void print_path(std::vector< Vertex<T>* >& path) {
	std::cout << "START ";
	for(auto v : path) {
		if(v->pred)
			std::cout << "-(" << v->pred->weight << ")-> ";
		std::cout << '|' << v->value << "| ";
	}
	std::cout << " END\n";
}

template <typename T>
std::vector< Vertex<T>* > store_path(Graph<T> &graph, Vertex<T>* src, Vertex<T>* dest) {
	using V = Vertex<T>;

	std::vector<V*> path;

	V* current = dest;

	if(*src == *dest) {
		//if we cant find a path return an empty vector
		//std::cout << "BFS : WARNING : No path found\n";
		std::vector<V*> empty;
		return empty;
	}

	while(*current != *src) {
		if(current->pred == nullptr) {
			//if we cant find a path return an empty vector
			//std::cout << "BFS : WARNING : No path found\n";
			std::vector<V*> empty;
			return empty;
		}
		path.push_back(current);
		current = current->pred->src;
	}

	//push the src as the last node
	path.push_back(src);

	std::reverse(path.begin(), path.end());

	return path;
}

}// namespace

//Algorithm taken from Intro to Algorithms 3e by Cormen, Lesierson, and Rivest
template <typename T>
std::vector< Vertex<T>* > bfs(Graph<T> graph, Vertex<T>* src, Vertex<T>* dest) {
	using V = Vertex<T>;

	std::queue<V*> q; //empty queue

	src->color = GRAY;
	src->d = 0;
	src->pred = nullptr;
	q.push(src);

	while(!q.empty()) {
		V* u = q.front();
		q.pop();

		auto adj_u = graph.get_adjacent_list(*u);
		for(auto edge : adj_u) {
			if(edge->dest->color == WHITE && edge->weight > 0) {
				edge->dest->color = GRAY;
				edge->dest->d = u->d + 1;
				//pred stores the edge used to get to the node
				// set the destinations pred equal to the current edge
				edge->dest->pred = edge;
				q.push(edge->dest);
			}
		}
		u->color = BLACK;
	}
	
	std::vector< Vertex<T>* > path = store_path(graph, src, dest);

	//if not found return empty
	return path;
}

#endif
