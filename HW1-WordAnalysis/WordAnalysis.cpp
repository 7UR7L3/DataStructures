// ==========================================
// Created: August 23, 2016
// @author Michael Rahn
//
// Description: Counts unique words in a file
// outputs the top N most common words
// ==========================================


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

#include <sstream>

using namespace std;

// struct to store word and count combinations
struct wordItem
{
	string word;
	int count;
};

/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into vector
* @param ignoreWordFile - filename (the file storing ignore words)
* @param _vecIgnoreWords - store ignore words from the file (pass by reference)
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords( char *ignoreWordFileName, vector< string > &_vecIgnoreWords );

/*
* Function name: isCommonWord
* Purpose: to see if a word is a common word
* @param word - a word (which you want to check if it is a common word)
* @param _vecIgnoreWords - the vector type of string storing ignore/common words
* @return - true (if word is a common word), or false (otherwise)
*/
bool isCommonWord( string word, vector< string > &_vecIgnoreWords );

/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to an array of wordItems
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN( wordItem wordItemList[], int topN );

const int STOPWORD_LIST_SIZE = 50;

// ./exec 10 HW1-HungerGames_edit.txt HW1-stopwords.txt

int main( int argc, char *argv[] )
{
	vector< string > vecIgnoreWords( STOPWORD_LIST_SIZE );

	if( argc != 4 ) // Verify we have the correct number of parameters, else throw error message and return.
	{
		cout << "Usage: " << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>" << endl;
		return 1;
	}

	// my code here

	return 0;
}

void getStopWords( char *ignoreWordFileName, vector< string > &_vecIgnoreWords )
{

}

bool isCommonWord( string word, vector< string > &_vecIgnoreWords )
{
	return true;
}

void printTopN( wordItem wordItemList[], int topN )
{

}