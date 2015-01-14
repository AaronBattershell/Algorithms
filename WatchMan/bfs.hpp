#ifndef BFS_HPP
#define BFS_HPP

#include "graph.hpp"

#include <iostream>

template <typename T>
std::vector< Edge<T> > bfs(Graph<T> g, Edge<T> src, Edge<T> dest);

#endif