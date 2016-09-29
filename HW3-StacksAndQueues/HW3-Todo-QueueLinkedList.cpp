#include "HW3-Todo-QueueLinkedList.hpp"
#include <iostream>

using namespace std;

TodoQueueLinkedList::TodoQueueLinkedList()
{
	queueFront = NULL;
	queueEnd = NULL;
}

bool TodoQueueLinkedList::isEmpty()
{
	return queueFront == NULL || queueEnd == NULL;
}

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

TodoItem* TodoQueueLinkedList::peek()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot peek." << endl;
		return NULL;
	}
	return queueFront;
}