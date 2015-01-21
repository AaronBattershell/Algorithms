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
		std::cout << "-(" << v->dtopred << ")-> " << v->value;
	}
	std::cout << '\n';
}

template <typename T>
void print_path(std::vector< Vertex<T>* > path) {
	std::cout << "START ";
	for(auto v : path) {
		std::cout << "-(" << v->dtopred << ")-> ";
		std::cout << '|' << v->value << "| ";
	}
	std::cout << " END\n";
}

template <typename T>
std::vector< Vertex<T>* > store_path(Graph<T> graph, Vertex<T>* src, Vertex<T>* dest) {
	using V = Vertex<T>;

	std::vector<V*> path;

	V* current = dest;
	path.push_back(current);

	while(*current != *src) {
		if(current->pred == nullptr) {
			//if we cant find a path return an empty vector
			std::cout << "No path found\n";
			std::vector<V*> empty;
			return empty;
		}
		current = current->pred;
		path.push_back(current);
	}

	std::reverse(path.begin(), path.end());

	return path;
}

}// namespace

//Algorithm taken from Intro to Algorithms 3e by Cormen, Lesierson, and Rivest
template <typename T>
std::vector< Vertex<T>* > bfs(Graph<T> graph, Vertex<T>* src, Vertex<T>* dest) {
	std::cout << "==BFS==\n";
	using V = Vertex<T>;

	std::queue<V*> q; //empty queue

	src->color = GRAY;
	src->d = 0;
	src->dtopred = 0;
	q.push(src);

	while(!q.empty()) {
		V* u = q.front();
		q.pop();

		auto adj_u = graph.get_adjacent_list(*u);
		for(auto edge : adj_u) {
			if(edge.vertex->color == WHITE && edge.weight > 0) {
				edge.vertex->color = GRAY;
				edge.vertex->d = u->d + 1;
				edge.vertex->pred = u;
				edge.vertex->dtopred = edge.capacity();
				q.push(edge.vertex);
			}
		}
		u->color = BLACK;
	}
	
	//print_path(graph, src, dest);
	std::vector< Vertex<T>* > path = store_path(graph, src, dest);
	print_path(path);

	//if not found return empty
	return path;
}

#endif