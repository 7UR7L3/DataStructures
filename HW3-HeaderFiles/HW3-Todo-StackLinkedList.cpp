#include "HW3-Todo-StackLinkedList.hpp"
#include <iostream>

using namespace std;

TodoStackLinkedList::TodoStackLinkedList()
{
	stackHead = NULL;
}

bool TodoStackLinkedList::isEmpty()
{
	return stackHead == NULL;
}

void TodoStackLinkedList::push( std::string todoItem )
{
	TodoItem* t = new TodoItem();
	t->todo = todoItem;

	t->next = stackHead;
	stackHead = t;
}

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

TodoItem* TodoStackLinkedList::peek()
{
	if( isEmpty() )
	{
		cout << "Stack empty, cannot peek." << endl;
		return NULL;
	}
	return stackHead;
}