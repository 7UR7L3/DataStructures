#include <iostream>
#include <fstream>  //allows istream/ostream
#include <string>
#include <cstdlib> 
#include <vector>
#include <sstream>      // std::stringstream, std::stringbuf

#include "Graph.hpp"

using namespace std;

void readFileIntoGraph(Graph & g, char* fileName);

int main(int argc, char*argv[])
{
    // Create a graph
    Graph graph;

    // Read file into graph
    readFileIntoGraph(graph, argv[1]);

	// Find districts
	graph.assignDistricts();

	graph.displayEdges();
    return 0;
}

void readFileIntoGraph(Graph & g, char* fileName)
{
    vector<string> cities;
    ifstream in_stream;
    //cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }

    string city;
    string line;
    getline(in_stream,line);
    std::stringstream ss(line);
    int y = 0;

    // Read a list of cities from the first line
    while (getline(ss,city,','))
    {
        if (city != "cities")
        {
            g.addVertex(city);
            cities.push_back(city);
        }
    }

    // Now read in all the vertices
    int i = 0;
    string in;
    while (!in_stream.eof())
    {
        i = -1;
        getline(in_stream,line);
        stringstream ss(line); 

        while (getline(ss,in,','))
        {
            if (i == -1)
            {
                city = in;
            }
            else
            {
                if (in != "-1" && in != "0")
                {
					int dist = atoi(in.c_str());
					cout << " ... Reading in " << city << " -- " << cities[i] << " -- " << dist << endl;
                    g.addEdge(city, cities[i], dist);
                }
            }
            i++;
        }
    }
}

