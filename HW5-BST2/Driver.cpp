// ==========================================
// Created: October 12, 2016
// @author Michael Rahn
//
// Homework 4
//
// CSCI2270 - Boese
//
// Description: Builds, searches, and traverses a BST.
// ==========================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstddef>

#include "MovieTree.cpp"

using namespace std;

// g++ -Wall -std=c++11 -o exec Driver.cpp
// ./exec HW4-Movies.txt
int main( int argc, char* argv[] )
{
	if( argc != 2 ) // Verify we have the correct number of parameters, else throw error message and return.
	{
		cout << "Usage: " << argv[0] << " <move information file>" << endl;
		return 1;
	}

	MovieTree* tree = new MovieTree();

	// Reads information from the input file into the tree.

	ifstream in;
	in.open( argv[1] );
	if( in.is_open() )
	{
		for( string line; getline( in, line ); )
		{
			string movie[4];
			istringstream ss( line );
			int i = 0;
			for( string info; getline( ss, info, ',' ); )
				movie[i++] = info;

			// Catches bad input.
			try{ stoi( movie[0] ); stoi( movie[2] ); stoi( movie[3] ); }
			catch( std::invalid_argument ){ cout << "Unable to Parse Information File. Terminating Program." << endl; return 2; }

			tree->addMovieNode( stoi( movie[0] ), movie[1], stoi( movie[2] ), stoi( movie[3] ) );
		}
	}

	// User input.
	for( string c;; )
	{
		cout << "======Main Menu======" << endl;
		cout << "1. Find a movie" << endl;
		cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl;
		cout << "4. Quit" << endl;

		getline( cin, c );

		if( c == "1" )
		{
			cout << "Enter title:" << endl;
			getline( cin, c );
			tree->findMovie( c );
		}
		else if( c == "2" )
		{
			cout << "Enter title:" << endl;
			getline( cin, c );
			tree->rentMovie( c );
		}
		else if( c == "3" )
		{
			tree->printMovieInventory();
		}
		else if( c == "4" ) break;
		else cout << "Invalid Input" << endl;
	}

	cout << "Goodbye!" << endl;
	return 0; // Program success.
}