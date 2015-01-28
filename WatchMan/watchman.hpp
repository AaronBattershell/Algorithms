#ifndef WATCHMAN_HPP
#define WATCHMAN_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "graph.hpp"
#include "bfs.hpp"
#include "parsing.hpp"
#include "ffs.hpp"
#include "intersection.hpp"
#include "inputData.h"

struct watchman {
	public:	
		inputData input;

		watchman(std::string fileName);
		void solve();

	private:
		void createWalls(std::vector<line> &straitWall, std::vector<arc> &curveWall);
		void findSightLines(std::vector<line> &straitWall, std::vector<arc> &curveWall, 
			Graph<int> &g, VertexFactory<int> *v);
		bool clearLineOfSight(line view, std::vector<line> &straitWall, std::vector<arc> &curveWall);
};

#endif
