#include "MovieTree.hpp"
#include <iostream>

using namespace std;

// Initializes the root to null.
MovieTree::MovieTree()
{
    root = NULL;
}

// Frees memory of every node in the tree via post-order traversal.
MovieTree::~MovieTree()
{
    DeleteAll( root );
}

// Helper method to print the entire tree.
void MovieTree::printMovieInventory()
{
    printMovieInventory( root );
}

// Counts the number of movies in the tree. Note that this does not print the output here
//   like every other method in this class.
int MovieTree::countMovieNodes()
{
    int* out = new int( 0 );
    countMovieNodes( root, out );
    return *out;
}

void MovieTree::deleteMovieNode( std::string title )
{
    MovieNode* n = search( title );
    if( n == NULL ) { cout << "Movie not found." << endl; return; }
    MovieNode* c = treeMinimum( n->rightChild );
    if( c == NULL ) // case where this doesn't have a right subtree to pull from
    {
        if( n->leftChild == NULL ) // case where this is a leaf node
        {
            if( n->parent == NULL ) // case where this is the only node in the tree
            {
                delete n;
                root = NULL;
            }
            else // case where this is a leaf node
            {
                if( n->parent->leftChild == n ) n->parent->leftChild = NULL; // case where this is on the left of the parent
                else n->parent->rightChild = NULL;
                delete n;
            }
        }
        else // case where this only has a left subtree
        {
            if( n->parent == NULL ) // case where this is the root
            {
                root = n->leftChild;
                root->parent = NULL;
                delete n;
            }
            else // case where this has a parent
            {
                if( n->parent->leftChild == n ) n->parent->leftChild = n->leftChild;
                else n->parent->rightChild = n->leftChild;
                n->leftChild->parent = n->parent;
                delete n;
            }
        }
    }
    else // case where this has a right subtree to pull from
    {
        n->ranking = c->ranking;
        n->title = c->title;
        n->year = c->year;
        n->quantity = c->quantity;

        if( c->parent != n ) c->parent->leftChild = c->rightChild;
        else c->parent->rightChild = c->rightChild;

        if( c->rightChild != NULL ) c->rightChild->parent = c->parent;
        delete c;
    }

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

//  Decrements the quantity of a movie if possible and removes it if it's the last in stock.
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

        if( n->quantity <= 0 ) deleteMovieNode( title );
    }
    else
    {
        cout << "Movie out of stock." << endl; // This will now never print because we remove before this case.
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

// Helper method to perform the tree deletion via post-order traversal.
void MovieTree::DeleteAll( MovieNode* node )
{
    if( node == NULL ) return;

    DeleteAll( node->leftChild );
    DeleteAll( node->rightChild );

    delete node;
}

// Helper method to count the number of movies in the tree.
// There is no reason to return by pointer here but ok, it can be a much more elegant one-line.
void MovieTree::countMovieNodes( MovieNode* node, int* c )
{
    if( node == NULL ) return;
    countMovieNodes( node->leftChild, c );
    countMovieNodes( node->rightChild, c );
    (*c)++;
}

// Helper method to find the minimum of a value node of a tree.
MovieNode* MovieTree::treeMinimum( MovieNode* node )
{
    if( node == NULL ) return NULL;
    MovieNode* min = node;
    for( ; min->leftChild != NULL; min = min->leftChild );
    return min;
}