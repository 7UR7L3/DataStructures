#include "HW3-Todo-StackArray.hpp"
#include <iostream>

using namespace std;

TodoStackArray::TodoStackArray()
{
	stackTop = -1;
}

bool TodoStackArray::isEmpty()
{
	return stackTop == -1;
}

bool TodoStackArray::isFull()
{
	return stackTop == MAX_STACK_SIZE - 1;
}

void TodoStackArray::push(std::string todoItem)
{
	if( isFull() )
	{
		cout << "Stack full, cannot add new todo item." << endl;
		return;
	}
	TodoItem* t = new TodoItem();
	t->todo = todoItem;
	stack[++stackTop] = t;
}

void TodoStackArray::pop()
{
	if( isEmpty() )
	{
		cout << "Stack empty, cannot pop an item." << endl;
		return;
	}
	TodoItem* toDel = stack[stackTop];
	stackTop--;
	delete toDel;
}

TodoItem* TodoStackArray::peek()
{
	if( isEmpty() )
	{
		cout << "Stack empty, cannot peek." << endl;
		return NULL;
	}
	return stack[stackTop];
}