#include "watchman.hpp"
using namespace std;

watchman::watchman(string fileName)
	:input(fileName) {
	
}

void watchman::solve() {
	while (input.get_next_problem()) {
			
		input.print_wallSet(input.wall_setVector);
    		input.print_paintSet(input.paint_setVector);
    		input.print_guardSet(input.guard_setVector);
	}
}	
