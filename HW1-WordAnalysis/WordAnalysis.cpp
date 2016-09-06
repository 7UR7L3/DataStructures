// ==========================================
// Created: August 23, 2016
// @author Michael Rahn
//
// Homework 1
//
// CSCI2270 - Boese
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
#include <unordered_map>
#include <algorithm>
#include <cstddef>

using namespace std;

// struct to store word and count combinations
struct wordItem
{
	string word;
	int count;
};

// A helper class to handle array resizing.
class MyWordVector
{
  public:
	int size = 0, arrSize = 100, doubled = 0;
	wordItem *words = new wordItem[arrSize];

	// Method to add an element to the end of the array - resizes *words if necessary.
	void add( wordItem w )
	{
		if( size >= arrSize ) // If array needs to be resized, create a new one, copy the old one, and delete the old one.
		{
			doubled++;
			wordItem *shameWeHaveToCopy = new wordItem[arrSize*2];
			for( int i = 0; i < arrSize; i++ ) shameWeHaveToCopy[i] = words[i];
			arrSize *= 2;
			delete [] words;
			words = shameWeHaveToCopy;

		}
		words[size] = w; // Add the element to the array.
		size++;
	}

	~MyWordVector()
	{
		delete [] words;
	}

	// Override [] to be able to access the array directly.
	wordItem& operator[]( int n ) { return words[n]; }
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
	if( argc != 4 ) // Verify we have the correct number of parameters, else throw error message and return.
	{
		cout << "Usage: " << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>" << endl;
		return 1;
	}

	// Get words that aren't to be considered.
	vector< string > ignoreWords( STOPWORD_LIST_SIZE );
	getStopWords( argv[3], ignoreWords );
	if( ignoreWords.empty() ) return 2;
	
	MyWordVector words; // The resizing array that keeps track of the number of resizes.

	// Go through the file specified containing the words.
	ifstream in;
	in.open( argv[2] );
	if( in.is_open() )
	{
		unordered_map< string, int > where; // Sacrifice memory for speed - hold indices of words with O(1) lookup.
		int uniqueTotal = 0, total = 0; // What needs to be outputted.

		for( string line; getline( in, line ); ) // Go through the lines of the file.
		{
			istringstream ss( line );
			for( string word; getline( ss, word, ' ' ); ) // Go through the words of the line.
				if( word != "" && !isCommonWord( word, ignoreWords ) ) // If this is a word we should consider.
				{
					total++;
					unordered_map< string, int >::const_iterator at = where.find( word );
					if( at == where.end() ) // If the word isn't in the array yet, add it.
					{
						wordItem w; w.word = word; w.count = 1; // The new word.
						words.add( w ); // Add the word to the resizing array.
						where.insert( { word, words.size - 1 } ); // Add the index to the word lookup.
						uniqueTotal++;
					}
					else words[ at->second ].count++; // Otherwise just increment the count of the word.
				}
		}

		// Print the output the specific way.
		sort( words.words, words.words + uniqueTotal, []( wordItem &a, wordItem &b ) -> bool{ return a.count > b.count; } ); // Sort before the print based on the count of the wordItem; based on http://stackoverflow.com/a/5123582 .
		printTopN( words.words, stoi( argv[1] ) );
		cout << "#" << endl;
		cout << "Array doubled: " << words.doubled << endl;
		cout << "#"<<endl;
		cout << "Unique non-common words: " << uniqueTotal << endl;
		cout << "#" << endl;
		cout << "Total non-common words: ";
		cout << total <<endl;
	}
	else // The file failed to open; alert the user and return an error.
	{
		cout << argv[2] << " failed to open." << endl;
		return 2;
	}

	return 0;
}

void getStopWords( char *ignoreWordFileName, vector< string > &_vecIgnoreWords )
{
	// Alert if the file couldn't be read, else add all words to the vector.
	ifstream inIgnore;
	inIgnore.open( ignoreWordFileName );
	if( inIgnore.is_open() ) for( string line; getline( inIgnore, line ); ) _vecIgnoreWords.push_back( line );
	else cout << ignoreWordFileName << " failed to open." << endl;
}

bool isCommonWord( string word, vector< string > &_vecIgnoreWords )
{
	// Checks all elements to see if the word should be ignored or not.
	for( string s : _vecIgnoreWords ) if( word == s ) return true;
	return false;
}

void printTopN( wordItem wordItemList[], const int topN )
{
	// Prints wordItem as "count - word".
	for( int i = 0; i < topN; i++ ) cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
}