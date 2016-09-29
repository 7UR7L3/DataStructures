#include "HW3-Todo-QueueLinkedList.hpp"
#include <iostream>

using namespace std;

//	initializes front and end pointers.
TodoQueueLinkedList::TodoQueueLinkedList()
{
	queueFront = NULL;
	queueEnd = NULL;
}

//	returns if either pointers don't point to anything in the queue.
bool TodoQueueLinkedList::isEmpty()
{
	return queueFront == NULL || queueEnd == NULL;
}

//	adds element to queue after queueEnd, setting queueFront if necessary.
void TodoQueueLinkedList::enqueue( std::string todoItem )
{
	TodoItem* t = new TodoItem();
	t->todo = todoItem;
	t->next = NULL;
	if( isEmpty() )
	{
		queueFront = t;
		queueEnd = t;
		return;
	}
	queueEnd->next = t;
	queueEnd = t;
}

//	removes element from queue if possible.
void TodoQueueLinkedList::dequeue()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot dequeue an item." << endl;
		return;
	}
	TodoItem* toSet = queueFront->next;
	delete queueFront;
	queueFront = toSet;
}

//	returns front of queue if possible.
TodoItem* TodoQueueLinkedList::peek()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot peek." << endl;
		return NULL;
	}
	return queueFront;
}