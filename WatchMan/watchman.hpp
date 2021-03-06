#ifndef WATCHMAN_HPP
#define WATCHMAN_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "graph.hpp"
#include "bfs.hpp"
#include "parsing.hpp"
#include "ffs.hpp"
#include "intersection.hpp"
#include "inputData.h"

struct watchman {
	public:	
		inputData input;
		std::fstream out;

		watchman(std::string inFileName, std::string outFileName);
		void solve();

	private:
		void createWalls(std::vector<line> &straitWall, std::vector<arc> &curveWall);
		void findSightLines(std::vector<line> &straitWall, std::vector<arc> &curveWall, 
			Graph<int> &g);
		bool clearLineOfSight(line view, std::vector<line> &straitWall, std::vector<arc> &curveWall);
		void printReuslt(Graph<int> g, int iter);
};

#endif
