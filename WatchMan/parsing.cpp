#include "parsing.hpp"

namespace {

void construct_graph(std::vector< std::queue<int> > input, Graph<int> &result) {
	using Vint = Vertex<int>;

	VertexFactory<int> *vf = result.vf;

	int count = 0;
	for(auto line : input) {
		Vint* curr = vf->make_vertex(count); //current vertex

		//if the line is empty simply add the vertex
		if(line.empty()) {
			result.add_vertex(curr);
		}
		// else add its edges
		else {
			//there must be an even number of ints
			assert(line.size() % 2 == 0);
			while(!line.empty()) {
				//make a vertex with the first number
				Vint* dest = vf->make_vertex(line.front());
				line.pop();
				//make the weight with the second number
				int weight = line.front();
				line.pop();
				result.add_edge(curr, dest, weight); //construct the edge
			}
		}

		count++;
	}
}

void print_graph_file(std::vector< std::queue<int> > input) {
	for(auto line : input) {
		if(line.empty()) {
			std::cout << "(empty)";
		}
		while(!line.empty()) {
			std::cout << line.front() << ' ';
			line.pop();
		}
		std::cout << '\n';
	}
}

}//namespace

void parse_bfs(std::string input, Graph<int> &g) {
	std::ifstream file(input);
	std::string line;
	std::vector< std::queue<int> > parsed_lines;

	while(!file.eof()) {
		//used to save the contents of the current line
		std::queue<int> current_line;

		//get the line from the file
		std::getline(file, line);

		//used to parse the individual numbers in the line
		std::string s;
		std::stringstream ss(line);

		if(line.empty()) {
			parsed_lines.push_back(current_line);
		}
		else {
			while(std::getline(ss, s, ' ')) {
				current_line.push(atoi(s.c_str()));
			}
			parsed_lines.push_back(current_line);
		}
	}

	print_graph_file(parsed_lines);
	construct_graph(parsed_lines, g);
}