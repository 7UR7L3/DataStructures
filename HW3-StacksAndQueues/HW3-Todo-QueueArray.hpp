#ifndef HW3_TODO_QUEUEARRAY
#define HW3_TODO_QUEUEARRAY

#include <string>

struct TodoItem
{
	std::string todo;
};

const int MAX_QUEUE_SIZE = 5;

class TodoQueueArray
{
  public:
	TodoQueueArray();
	bool isEmpty();
	bool isFull();
	void enqueue(std::string todoItem);
	void dequeue();
	TodoItem* peek();

	/* for grading purposes we need these following methods */
	int getQueueFront()	 { return queueFront; }
	int getQueueEnd()	 { return queueEnd; }
	TodoItem** getQueue() { return queue; }

  private:
	int queueFront;
	int queueEnd;
	TodoItem* queue[MAX_QUEUE_SIZE];
};

#endif
