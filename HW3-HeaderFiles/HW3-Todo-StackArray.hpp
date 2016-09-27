#ifndef HW3_TODO_STACKARRAY
#define HW3_TODO_STACKARRAY

#include <string>

struct TodoItem
{
	std::string todo;
};

const int MAX_STACK_SIZE = 5;

class TodoStackArray
{
  public:
	TodoStackArray();
	bool isEmpty();
	bool isFull();
	void push(std::string todoItem);
	void pop();
	TodoItem* peek();

	/* for grading purposes we need these following methods */
	int getStackTop()	 { return stackTop; }
	TodoItem** getStack() { return stack; }

  private:
	int stackTop;
	TodoItem* stack[MAX_STACK_SIZE];
};

#endif
