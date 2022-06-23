#include <iostream>

#include "Graph.h"
#include "tarjan.h"

int main(int argc, char** argv) {

	Graph graph{8};

	graph.AddEdge(1, 0);
	graph.AddEdge(2, 1);
	graph.AddEdge(2, 3);
	graph.AddEdge(3, 2);
	graph.AddEdge(0, 7);
	graph.AddEdge(7, 1);
	graph.AddEdge(6, 7);
	graph.AddEdge(6, 1);
	graph.AddEdge(5, 6);
	graph.AddEdge(6, 5);
	graph.AddEdge(4, 5);
	graph.AddEdge(4, 4);
	graph.AddEdge(4, 3);

	auto const cycles = tarjanFindComponents(graph);
	for(auto const& cycle : cycles) {
		std::cout << "[ ";
		for(auto const& vertex : cycle) {
			std::cout << vertex << ", ";
		}
		std::cout << "]\n";
	}

	std::flush(std::cout);

	return 0;
}