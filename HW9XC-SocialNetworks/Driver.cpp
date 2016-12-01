#include <iostream>
#include <fstream>  //allows istream/ostream
#include <string>
#include <cstdlib> 
#include <vector>
#include <array>
#include <queue>
#include <sstream>      // std::stringstream, std::stringbuf

#include "Graph.hpp"

using namespace std;

void readUsersIntoGraph(Graph &g, char* fileName);
void readFilesIntoGraph(Graph & g, char* directoryName);

int main(int argc, char*argv[])
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " datasetDirectoryName idlistFilename" << endl;
		return -1;
	}

    // Create a graph
    Graph graph;

    // Read file into graph
	readUsersIntoGraph(graph, argv[2]);	// file is just a list of all userids
    readFilesIntoGraph(graph, argv[1]); // each userid's detailed info

	graph.assignSocialCircles();

	cout << "========================================\n";
	cout << "GRAPH CONNECTIONS ====================== " << endl;
	graph.displayEdges();

	graph.displayHobbies();

    return 0;
}

/* Function to read in all the ids in the social network.
  Does not have access to their name and hobbies, just a list of ids
  Reads in from the filename listed in command-line arguments
  @param network the graph data structure of the social network
  @param fileName is the file with a list of IDs in the social network
  */
void readUsersIntoGraph(Graph & network, char* fileName)
{
	cout << "Creating graph of social network ids from file: " << fileName << endl;
	ifstream in;
	in.open( fileName );
	if( in.is_open() )
		for( string line; getline( in, line ); ) // add each vertex to the network
			network.addVertex( line );
	else cout << fileName << " could not be opened." << endl;
	in.close();
}

/*
 * reads all files (one at a time) from the dataset into the graph
 * @param directoryName name of the directory with all the dataset files
 * @param fileName name of file with a list of IDs needed to process in directory
 */
void readFilesIntoGraph(Graph & g, char* directoryName)
{
    cout << "Processing dataset: " << directoryName << " (" << g.vertices.size() << " files)" << endl;
	int numCollisions = 0;

	// loop through each vertex and read in its detailed information
	//	each vertex in the graph has the userid which you can create the filename to read
	// hint: create a string with directoryname/userid.txt to open each file
	
	for( uint i = 0; i < g.vertices.size(); i++ )
	{
		ifstream in;
		in.open( string( directoryName ) + "/" + g.vertices[i].id + ".txt" );
		if( in.is_open() )
		{
			string line;
			getline( in, line ); // discard first line
			getline( in, line ); // get name
			g.vertices[i].name = line;
			getline( in, line ); // get hobbies
			istringstream ss( line );
			for( string hobby; getline( ss, hobby, ',' ); )
				numCollisions += g.addUserToHobby( hobby, g.vertices[i].id );
			for( ;getline( in, line ); ) // get friends
				g.addEdge( g.vertices[i].id, line );
		}
		else cout << string( directoryName ) + "/" + g.vertices[i].id + ".txt" << " could not be opened." << endl;
		in.close(); // this is included as per comment below despite being in the ifstream's destructor as c++ programming convention
	}

	// close files when done with each!!
	cout << "========================================\n";
	cout << " NUMBER OF COLLISIONS ON ADDING HOBBIES: " << numCollisions << endl;
}

