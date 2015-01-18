#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "graph.hpp"

template <typename T>
Graph<T> parse_bfs(std::string input) {
	std::ifstream file(input);
	//TODO: the rest of parsing for BFS files
	Graph<T> result;
	return result;
}

#endif