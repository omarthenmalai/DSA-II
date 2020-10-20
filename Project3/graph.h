#ifndef _GRAPH_H
#define _GRAPH_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <sstream>

#include "hash.h"
#include "heap.h"



class Graph 
{
    private:
        class Vertex 
	{
            public:
                std::string name;
                std::list<std::pair<Vertex*, int> > *adj;
                Vertex *prev;
                bool isKnown;
                int distance;
		Vertex(std::string v_name);
        };
        std::vector<Vertex*> vertexList;
        hashTable *vertexLookup;

	Vertex *create_vertex(const std::string vertex_name);
	Vertex *get_vertex(const std::string vertex_name);		
    public:
        Graph(const std::string &graph);
        void print_graph(const std::string &ofile, const std::string &start);
        void dijkstra(const std::string start);
	bool contains(const std::string &start);

};

#endif //_GRAPH_H
