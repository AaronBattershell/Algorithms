#include "graph.hpp"
#include "bfs.hpp"
#include "parsing.hpp"
#include "ffs.hpp"
#include "watchman.hpp"
#include <string>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
 
	if (argc < 2) {
		std::cout << "Watch, Man! Program Parameters:" << std::endl;
		std::cout << "\tBFS Test      : -b [INPUT_FILE_NAME] [START_NODE] [END_NODE]" << std::endl;
		std::cout << "\tFord-Folkerson: -f [INPUT_FILE_NAME]" << std::endl;
		std::cout << "\tMuseum Problem: -m [INPUT_FILENAME] [OUTPUT_FILENAME]" << std::endl;
		
		return -1;	
	}

	//some aliases
	using Vint = Vertex<int>;
	using Eint = Edge<int>;
	using al = AdjacencyList<Eint>;
	
	Graph<int> g;
	VertexFactory<int>* vf = g.vf;

	//read the option. can be -b(bfs), -f(ford-folkerson), -m (museum)
	std::string opt;

	opt = argv[1]; //option

	if(opt == "-b") {
		//check arg count
		if(argc != 5) {
			std::cout << "Not enough parameters given.\n";
			std::cout << "Found " << argc << " parameters. Need " << 5 << " parameters.\n";
			return -1;
		}

		std::cout << "You have chosen BFS with file " << argv[2]
				  << ". Finding path from " << argv[3] << " to " << argv[4] 
				  << '\n';

		// testing vertex factory is return old pointers above
		Vint* src = vf->make_vertex( atoi(argv[3]) );
		Vint* dest = vf->make_vertex( atoi(argv[4]) );
		std::cout << "===File Contents===\n";
		//parse the file and put the vertices into the graph
		parse_bfs(argv[2], g);
		std::cout << "===Graph Adjacency List===\n";
		g.print();
		std::cout << "===PATH===\n";
		std::cout << "==BFS==\n";

		std::chrono::time_point<std::chrono::system_clock> start, end;
    	start = std::chrono::system_clock::now();

		auto path = bfs(g, src, dest);


		print_path(path);
		end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end-start;
    	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    	std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}
	else if(opt == "-f") {
		std::cout << "You have chosen Ford-Fulkerson with file " << argv[2] << '\n';
		std::cout << "===File Contents===\n";
		parse_bfs(argv[2], g);
		std::cout << "===Graph Adjacency List===\n";
		g.print();
		std::cout << "Source nodes: \n";
		Vertex<int>* src = vf->make_vertex(get_src(g).value);
		std::cout << "Sink nodes: \n";
		Vertex<int>* sink = vf->make_vertex(get_sink(g).value);

		std::chrono::time_point<std::chrono::system_clock> start, end;
    	start = std::chrono::system_clock::now();

		g = ford_fulkerson(g, src, sink);

		end = std::chrono::system_clock::now();

		int max_flow = get_max_flow(g, sink);
	    std::cout << "Max flow= " << max_flow << '\n';

	    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::chrono::duration<double> elapsed_seconds = end-start;
 
    	std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}
	else if(opt == "-df") {
		std::cout << "You have chosen Ford-Fulkerson with file " << argv[2] << '\n';
		std::cout << "===File Contents===\n";
		parse_bfs(argv[2], g);
		std::cout << "===Graph Adjacency List===\n";
		g.print();
		std::cout << "Source nodes: \n";
		Vertex<int>* src = vf->make_vertex(get_src(g).value);
		std::cout << "Sink nodes: \n";
		Vertex<int>* sink = vf->make_vertex(get_sink(g).value);

		std::chrono::time_point<std::chrono::system_clock> start, end;
    	start = std::chrono::system_clock::now();

		g = ford_fulkerson_detailed(g, src, sink);

		end = std::chrono::system_clock::now();

		int max_flow = get_max_flow(g, sink);
	    std::cout << "Max flow= " << max_flow << '\n';

	    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::chrono::duration<double> elapsed_seconds = end-start;
 
    	std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}
	else if(opt == "-m") {
		if (argc != 4) {
			std::cout << "Not enough parameters given.\n";
			std::cout << "Found " << argc << " parameters. Need " << 4 << " parameters.\n";
			return -1;
		}

		std::cout << "You have chosen Museum Problem with file " << argv[2] << '\n';

		std::chrono::time_point<std::chrono::system_clock> start, end;
    	start = std::chrono::system_clock::now();

		watchman(argv[2], argv[3]).solve();

		end = std::chrono::system_clock::now();

		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::chrono::duration<double> elapsed_seconds = end-start;
    	
 
    	std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}

	delete vf;

	return 0;
}

