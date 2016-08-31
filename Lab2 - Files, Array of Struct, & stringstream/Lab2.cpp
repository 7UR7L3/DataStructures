// g++ -Wall -std=c++11 -o exec Lab2.cpp && ./exec

//#pragma once	//	Equivalent to header guards.

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>

#include <vector>

#include <algorithm>

using namespace std;

struct Car
{
	string model, make, year;
	Car( string mo, string ma, string ye )
	{
		model = mo;
		make = ma;
		year = ye;
	}
};

bool compareCars( Car a, Car b );

int main( int argc, char *argv[] )
{
	ifstream fromFile;
	string text = "";
	if( argc <= 1 ) return 1; // This program needs a command line argument to specify the file to read input from.
	fromFile.open( argv[1] );
	if( fromFile.is_open() )
	{
		vector<Car> cars;
		while( getline( fromFile, text ) )
		{
			istringstream ss( text );
			string token;
			string tokens[3];
			for( int i = 0; getline( ss, token, ' ' ); i++ ) tokens[i] = token;
			cars.push_back( Car( tokens[0], tokens[1], tokens[2] ) );
		}
		fromFile.close();
		sort( cars.begin(), cars.end(), compareCars );
		for( Car c : cars ) cout << c.model << " " << c.make << " " << c.year << endl;
	}
	else
	{
		cout << "File failed to open." << endl;
		return 2;
	}
	return 0;
}

bool compareCars( Car a, Car b )
{
	return a.model.compare( b.model ) < 0;
}