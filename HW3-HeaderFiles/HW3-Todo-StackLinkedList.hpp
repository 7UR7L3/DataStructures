#ifndef HW3_TODO_STACKLINKEDLIST
#define HW3_TODO_STACKLINKEDLIST

#include <string>

struct TodoItem
{
	std::string todo;
	TodoItem *next;
};

class TodoStackLinkedList
{
  public:
	TodoStackLinkedList();
	bool isEmpty();
	void push(std::string todoItem);
	void pop();
	TodoItem* peek();

	/* for grading purposes we need these following methods */
	TodoItem* getStackHead()	 { return stackHead; }

  private:
	TodoItem* stackHead;
};

#endif
