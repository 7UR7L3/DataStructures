#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addEdge(string v1, string v2, int dist)
{
    adjVertex c;
    c.distance = dist;
    c.v = findVertex( v2 );
    findVertex( v1 )->adj.push_back( c );
}

void Graph::addVertex(string n)
{
    vertex v;
    v.name = n;
    v.district = -1;
    v.visited = false;
    v.adj = std::vector<adjVertex>();
    vertices.push_back( v );
}

void Graph::displayEdges()
{
    for(uint i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].district << ":" <<vertices[i].name << "-->";
        for(uint j = 0; j < vertices[i].adj.size(); j++)
        {
            cout << vertices[i].adj[j].v->name;
            cout << " (" << vertices[i].adj[j].distance << " miles)"; 
            if (j != vertices[i].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}

void Graph::assignDistricts()
{
    // Starting district numbers at 1
    int distID = 1;

    // For each of the vertices
    for(uint i = 0; i < vertices.size(); i++)
    {
        // Only consider a vertex that has not been assigned a district.
        if (vertices[i].district == -1)
        {
            // Run breadth first traversal and assign each node in the network to this district.
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }
    }
}

void Graph::BFTraversalLabel(std::string startingCity, int distID)
{
    queue<vertex*> q;
    // Label all as unvisited.
    for(uint i = 0; i < vertices.size(); i++)
    {
       vertices[i].visited = false;
    }
    // Find the starting node and enqueue it.
    for(uint i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == startingCity)
        {
            q.push( &vertices[i] );
            break;
        }
    }
    // Now do the rest of the search.
    while (q.empty() != true)
    {
        vertex * u = q.front();        // get the next one from the queue
        q.pop();                        // remove that one from the queue
        // add code here
        if( !u->visited )
        {
            for( adjVertex a : u->adj ) if( !a.v->visited ) q.push( a.v );
            u->visited = true;
            u->district = distID;
        }
    }
}

vertex * Graph::findVertex(std::string name)
{
    for(uint i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
        {
            return &vertices[i];
        }
    }
    return NULL;
}
