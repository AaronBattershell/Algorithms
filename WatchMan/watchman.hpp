#ifndef WATCHMAN_HPP
#define WATCHMAN_HPP

#include <string>
#include <iostream>
#include "intersection.hpp"
#include "inputData.h"

struct watchman {
	inputData input;

	watchman(std::string fileName);
	void solve();
};

#endif
