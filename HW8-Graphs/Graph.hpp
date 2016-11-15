#ifndef GRAPH_HPP
#define GRAPH_HPP

#include<vector>
#include<iostream>

struct vertex;

/*This is the struct for the adjacent vertices for each
 vertex in the graph. */
struct adjVertex
{
	vertex *v;
	int distance;
};

/*this is the struct for each vertex in the graph.  */
struct vertex
{
    int ID;
    std::string name;
    int district;
    bool visited;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int distance);
        void addVertex(std::string name);
        void displayEdges();
        void assignDistricts();

    private:
        std::vector<vertex> vertices;
        vertex * findVertex(std::string name);
        //call BFTraversalLabel from within assignDistricts to label the districts.
        //This method should implement a breadth first traversal from the startingCity
        //and assign all cities encountered the distID value
        void BFTraversalLabel(std::string startingCity, int distID);
};

#endif // GRAPH_HPP
