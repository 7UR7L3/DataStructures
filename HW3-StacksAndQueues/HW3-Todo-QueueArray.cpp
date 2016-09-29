#include "HW3-Todo-QueueArray.hpp"
#include <iostream>

using namespace std;

TodoQueueArray::TodoQueueArray()
{
	queueFront = 0;
	queueEnd = -2;
}

bool TodoQueueArray::isEmpty()
{
	return queueEnd == -2;
}

bool TodoQueueArray::isFull()
{
	return (queueEnd + 1) % MAX_QUEUE_SIZE == queueFront;
}

void TodoQueueArray::enqueue( std::string todoItem )
{
	if( isFull() )
	{
		cout << "Queue full, cannot add new todo item." << endl;
		return;
	}
	queueEnd = (queueEnd == -2) ? 0 : ((queueEnd+1) % MAX_QUEUE_SIZE);
	TodoItem* t = new TodoItem();
	t->todo = todoItem;
	queue[queueEnd] = t;
}

void TodoQueueArray::dequeue()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot dequeue an item." << endl;
		return;
	}
	if( queueFront == queueEnd )
	{
		delete queue[queueFront];
		queueEnd = -2;
		return;
	}
	delete queue[queueFront];
	queueFront = (queueFront+1) % MAX_QUEUE_SIZE;

}

TodoItem* TodoQueueArray::peek()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot peek." << endl;
		return NULL;
	}
	return queue[queueFront];
}