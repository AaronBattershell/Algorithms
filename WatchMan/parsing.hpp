#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <queue>
#include <stdlib.h>
#include "graph.hpp"

Graph<int> parse_bfs(std::string input, VertexFactory<int>* vf);

#endif