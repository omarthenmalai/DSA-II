#include "graph.h"

int main()
{
	std::string graph_name;
	std::string start, output_file;
	
	std::cout << "Enter name of graph file: ";
	std::cin >> graph_name;
	
	auto graph = Graph(graph_name);
	do
	{
		std::cout << "Enter a valid vertex id for the starting vertex: ";
		std::cin >> start;
	}while(!graph.contains(start));
	
	clock_t t1 = clock();
    graph.dijkstra(start);
    clock_t t2 = clock();
	
	double time = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";

	std::cout << "Enter name of output file: ";
    std::cin >> output_file;
    graph.print_graph(output_file, start);

    return 0;	
}