#include "graph.h"

Graph::Graph(const std::string &graph)
{
		vertexLookup = new hashTable(hashTable::primes[0]);
		std::ifstream input(graph);
		if(input.is_open())
		{
			std::string line;
			while(getline(input, line)) 
			{
				std::string src, dest;
				int cost;
				Vertex *start, *end;
				std::istringstream stream (line);
				stream >> src >> dest >> cost;
				start = create_vertex(src);
				end = create_vertex(dest);
				start->adj->push_back({end, cost});
			}
		}
}

Graph::Vertex *Graph::create_vertex(const std::string vertex_name)
{
	Vertex *v = new Graph::Vertex(vertex_name);
	vertexLookup->insert(vertex_name, v);
	vertexList.push_back(v);
	return v;
}

Graph::Vertex *Graph::get_vertex(const std::string vertex_name)
{
	Vertex *v = static_cast<Vertex *>(vertexLookup->getPointer(vertex_name, nullptr));
	return v;
}

bool Graph::contains(const std::string &start)
{
	return vertexLookup->contains(start);
}

void Graph::print_graph(const std::string &ofile, const std::string &start)
{
	std::ofstream output(ofile);
	for(auto v : vertexList)
	{
		int dist = v->distance;
		output << v->name <<": ";
		std::vector<std::string> path;
		path.push_back(v->name);
		while(v->prev != nullptr)
		{
			path.push_back(v->prev->name);
		}
		
		if(v->name == start)
		{
			output << dist <<" [";
			for(int i = path.size()-1; i>=0; i--)
			{
				output << path[i];
				if(i)
					output << ", ";
			}
			output << "]" << std::endl;
		}
		else
			output << "NO PATH" << std::endl;
	}
}

Graph::Vertex::Vertex(std::string v_name): name(v_name)
{
	adj = new std::list<std::pair<Vertex*, int>>();
	distance = 0;
	prev = nullptr;
	isKnown = false;	
}

void Graph::dijkstra(const std::string start)
{
	heap h(this->vertexList.size() + 1);
	std::vector<Vertex*>::iterator it;

	for(it=this->vertexList.begin(); it!=this->vertexList.end();it++) 
	{
        if((*it)->name==start)
            (*it)->distance = 0;
        else
            (*it)->distance = std::numeric_limits<int>::max();
        
        (*it)->isKnown = false;
        (*it)->prev = NULL;
        h.insert((*it)->name,(*it)->distance,(*it));
    }
	
	while(!(h.isEmpty()))
	{
		Vertex *v;
		h.deleteMin(NULL, NULL, &v);
		v->isKnown = true;
		for(auto it=v->adj->begin(); it!=v->adj->end();it++)
		{
			if(it->first->isKnown)
				continue;
			int cost = it->second;
			
			if(v->distance+cost<it->first->distance)
			{
				if(h.setKey(it->first->name, v->distance+cost) != 0)
	
					std::cout << it->first->name << " " << v->distance+cost << "failed" << std::endl;
				else
					it->first->distance = v->distance+cost;
					it->first->prev = v;
			}
		}
	}	
}