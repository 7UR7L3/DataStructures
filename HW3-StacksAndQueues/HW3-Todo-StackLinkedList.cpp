#include "HW3-Todo-StackLinkedList.hpp"
#include <iostream>

using namespace std;

//	initalizes the head of the stack.
TodoStackLinkedList::TodoStackLinkedList()
{
	stackHead = NULL;
}

//	returns if the head doesn't point to a todo item.
bool TodoStackLinkedList::isEmpty()
{
	return stackHead == NULL;
}

//	adds element to stack.
void TodoStackLinkedList::push( std::string todoItem )
{
	TodoItem* t = new TodoItem();
	t->todo = todoItem;

	t->next = stackHead;
	stackHead = t;
}

//	removes element from stack if possible.
void TodoStackLinkedList::pop()
{
	if( isEmpty() )
	{
		cout << "Stack empty, cannot pop an item." << endl;
		return;
	}
	TodoItem* toDel = stackHead;
	stackHead = stackHead->next;
	delete toDel;
}

//	returnes element at head of stack if possible.
TodoItem* TodoStackLinkedList::peek()
{
	if( isEmpty() )
	{
		cout << "Stack empty, cannot peek." << endl;
		return NULL;
	}
	return stackHead;
}