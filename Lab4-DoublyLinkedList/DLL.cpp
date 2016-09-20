#include <iostream>
#include <cstddef>

using namespace std;

//node implementation for doubly linked list
struct Node
{
	int key;
	Node *previous;
	Node *next;
};

void insertAtEnd( int key, Node* end )
{
	Node* toAdd = new Node();
	
	toAdd->key = key;
	toAdd->previous = end->previous;
	toAdd->next = end;

	end->previous->next = toAdd;
	end->previous = toAdd;
}

void printBackwards( Node* end )
{
	for( end = end->previous; end->previous != NULL; end = end->previous )
		cout << end->key << endl;
}

int main()
{
	Node start, end;
	
	start.key = -1;
	start.previous = NULL;
	start.next = &end;

	end.key = -1;
	end.previous = &start;
	end.next = NULL;

	for( int i = 0; i < 10; i++ ) insertAtEnd( i, &end );
	printBackwards( &end );

	return 0;
}