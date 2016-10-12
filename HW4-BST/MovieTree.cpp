#include "MovieTree.hpp"
#include <iostream>

using namespace std;

// Initializes the root to null.
MovieTree::MovieTree()
{
    root = NULL;
}

// Frees memory of every node in the tree.
MovieTree::~MovieTree()
{
    // We do not implement this for HW4.
}

// Helper method to print the entire tree.
void MovieTree::printMovieInventory()
{
    printMovieInventory( root );
}

// Adds a new node based on information to the tree.
void MovieTree::addMovieNode( int ranking, std::string title, int releaseYear, int quantity )
{
    // The new node.
    MovieNode* n = new MovieNode( ranking, title, releaseYear, quantity );
    n->leftChild = NULL;
    n->rightChild = NULL;
    n->parent = NULL;

    // Sets root to the node if it's the first element in the tree, otherwise find and add to the tree.
    if( root == NULL ) root = n;
    else
        for( MovieNode* on = root;; )
        {
            bool toLeft = n->title < on->title;
            if( toLeft && on->leftChild == NULL ){ on->leftChild = n; n->parent = on; break; }
            else if( !toLeft && on->rightChild == NULL ){ on->rightChild = n; n->parent = on; break; }
            on = toLeft ? on->leftChild : on->rightChild;
        }
}

//  Prints the results of a movie search.
void MovieTree::findMovie( std::string title )
{
    MovieNode* n = search( title );
    if( n == NULL ) cout << "Movie not found." << endl;
    else
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << n->ranking << endl;
        cout << "Title:" << n->title << endl;
        cout << "Year:" << n->year << endl;
        cout << "Quantity:" << n->quantity << endl;
    }
}

//  Decrements the quantity of a movie if possible.
void MovieTree::rentMovie( std::string title )
{
    MovieNode* n = search( title );
    if( n == NULL ) cout << "Movie not found." << endl;
    else if( n->quantity > 0 )
    {
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << n->ranking << endl;
        cout << "Title:" << n->title << endl;
        cout << "Year:" << n->year << endl;
        cout << "Quantity:" << --n->quantity << endl;
    }
    else
    {
        cout << "Movie out of stock." << endl;
    }
}

// Recurses through the tree in an inorder traversal, printing the title and quantity of every MovieNode.
void MovieTree::printMovieInventory( MovieNode* node )
{
    if( node == NULL ) return;
    printMovieInventory( node->leftChild );
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    printMovieInventory( node->rightChild );

}

// Helper method to perform the search recursively.
MovieNode* doSearch( MovieNode* on, std::string title )
{
    if( on == NULL ) return NULL;
    if( on->title == title ) return on;
    MovieNode* l = doSearch( on->leftChild, title );
    MovieNode* r = doSearch( on->rightChild, title );
    if( l != NULL ) return l;
    if( r != NULL ) return r;
    return NULL;
}

// This is a private helper method to search for a title...... sure...
MovieNode* MovieTree::search( std::string title )
{
    return doSearch( root, title );
}