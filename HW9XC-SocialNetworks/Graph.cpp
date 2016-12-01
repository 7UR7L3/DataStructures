#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

Graph::Graph() 
{
	// allocate memory for hobbies
	for( uint i = 0; i < HASHMAP_SIZE; i++ )
	{
		hobbies[i] = new hobbylist();
		hobbies[i]->hobby = "";
	}
}

Graph::~Graph() 
{ 
	// loop through array freeing each hobbylist
	for( uint i = 0; i < HASHMAP_SIZE; i++ )
	{
		vector<vertex*>().swap( hobbies[i]->list ); // swaps list with empty vector to deallocate memory
		delete hobbies[i];
	}
}

void Graph::addEdge(string v1, string v2)
{
	if(v1 == v2) 	// don't add self 
		return;

	vertex *vertex1 = findVertex(v1);
	vertex *vertex2 = findVertex(v2);

	for( uint i = 0; i < vertex1->friends.size(); i++ ) if( vertex1->friends[i].v->id == v2 ) return; // the friendship has previously been established
	// otherwise create asjVertex's and add them to each friend
	adjVertex v1f;
	v1f.v = vertex2;
	adjVertex v2f;
	v2f.v = vertex1;
	vertex1->friends.push_back( v1f );
	vertex2->friends.push_back( v2f );

}

/* add the person to the graph */
void Graph::addVertex(string id)
{
	// create vertex to be filled with information later and add it to the list of all vertices
	vertex toAdd;
	toAdd.id = id;
	toAdd.networkID = 0;
	vertices.push_back( toAdd );
}

void Graph::displayEdges()
{
	//	loop through all vertices and all friends of those vertices printing all friends
	for( uint i = 0; i < vertices.size(); i++ )
	{
        cout << vertices[i].networkID << ": [" << vertices[i].id << "] " << vertices[i].name << "-->" << vertices[i].friends[0].v->name;
        for( uint j = 1; j < vertices[i].friends.size(); j++ ) cout << "***" << vertices[i].friends[j].v->name;
		cout << endl;
	}
}

int Graph::addUserToHobby(std::string hobby, std::string id)
{
	// cout << "Adding to hobby: " << hobby << " user: " << id << endl;
	vertex *user = findVertex(id);
	// initial key is based on the first 2 characters of the hobby name
	int key = (hobby[0] + hobby[1]) % HASHMAP_SIZE;
	//cout << " initial hashmap key " << key << endl;
	int collisions = 0;
	int i = key;
	for( ; hobbies[i]->hobby != hobby && hobbies[i]->hobby != ""; i = (i+1) % HASHMAP_SIZE, collisions++ ); // find where to insert the hobby, incrementing collisions
	if( hobbies[i]->hobby != hobby ) hobbies[i]->hobby = hobby; // set the slot to the hobby if it isn't already set
	hobbies[i]->list.push_back( user );


	return collisions;
}

void Graph::displayHobbies()
{
	cout << "========================================\n";
	cout << "DISPLAYING HOBBY INTERESTS =============" << endl;
	// loop through entire hashtable printing each hobby and which users have that hobby
	for( uint i=0; i<HASHMAP_SIZE; i++)
		if( hobbies[i]->hobby != "" )
		{
			cout << hobbies[i]->hobby << ": " << hobbies[i]->list[0]->name;
			for( uint j = 1; j < hobbies[i]->list.size(); j++ )
				cout << ", " << hobbies[i]->list[j]->name;
			cout << endl;
		}
}

/* return pointer to the correct vertex (person)  */
vertex * Graph::findVertex(std::string id)
{
	for( uint i = 0; i < vertices.size(); i++ ) if( vertices[i].id == id ) return &vertices[i]; // return if it's found
	return NULL; // else return NULL indicating it isn't in vertices
}

void Graph::assignSocialCircles()
{
	int circle = 1; // the first circle is circle 1
	for( uint i = 0; i < vertices.size(); i++ )
		if( vertices[i].networkID == 0 ) // only traverse over new social circles
			BFTraversalLabel( vertices[i].id, circle++  );
}

void Graph::BFTraversalLabel(std::string userid, int groupID)
{
	queue< vertex* > q;
	vertex* on = findVertex( userid );
	q.push( on );
	for( ;q.size() > 0; )
	{
		on = q.front();
		q.pop();
		if( on->networkID == 0 ) // only add to the queue when at an unvisited person, setting that person's circle
		{
			on->networkID = groupID;
			for( uint i = 0; i < on->friends.size(); i++ )
				q.push( on->friends[i].v );
		}
	}
}

