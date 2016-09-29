#include "HW3-Todo-StackArray.hpp"
#include <iostream>

using namespace std;

//	initializes top of stack index.
TodoStackArray::TodoStackArray()
{
	stackTop = -1;
}

//	case where there are no elements in the stack.
bool TodoStackArray::isEmpty()
{
	return stackTop == -1;
}

//	case where the top of the stack points to the last slot in the array.
bool TodoStackArray::isFull()
{
	return stackTop == MAX_STACK_SIZE - 1;
}

//	adds an element if there is size.
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

//	removes an element if there exists one to be removed.
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

//	returns item at top of stack if such an item exists.
TodoItem* TodoStackArray::peek()
{
	if( isEmpty() )
	{
		cout << "Stack empty, cannot peek." << endl;
		return NULL;
	}
	return stack[stackTop];
}