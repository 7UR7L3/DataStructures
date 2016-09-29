#include "HW3-Todo-QueueArray.hpp"
#include <iostream>

using namespace std;

//	sets up front and end.
TodoQueueArray::TodoQueueArray()
{
	queueFront = 0;
	queueEnd = -2;
}

//	set end to be -2 representing an empty queue.
bool TodoQueueArray::isEmpty()
{
	return queueEnd == -2;
}

//	check if end is exactly one before front considering the array to be circular.
bool TodoQueueArray::isFull()
{
	return (queueEnd + 1) % MAX_QUEUE_SIZE == queueFront;
}

//	adds item to queue.
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

//	removes item from queue.
void TodoQueueArray::dequeue()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot dequeue an item." << endl;
		return;
	}
	if( queueFront == queueEnd )	//	special case if exactly one element left. have to set end to -2.
	{
		delete queue[queueFront];
		queueEnd = -2;
		return;
	}
	delete queue[queueFront];
	queueFront = (queueFront+1) % MAX_QUEUE_SIZE;

}

//	returns element next to be dequeued if such an element exists.
TodoItem* TodoQueueArray::peek()
{
	if( isEmpty() )
	{
		cout << "Queue empty, cannot peek." << endl;
		return NULL;
	}
	return queue[queueFront];
}