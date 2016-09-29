//#include "HW3-Todo-QueueArray.hpp"
//#include "HW3-Todo-QueueLinkedList.hpp"
//#include "HW3-Todo-StackArray.hpp"
#include "HW3-Todo-StackLinkedList.hpp"

#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	TodoStackLinkedList* a = new TodoStackLinkedList();
	for( int i = 0; i < 10; i++ )
	{
		if( a->peek() != NULL ) cout << a->peek()->todo << endl;
		string s = static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << i ) ).str() + "..string";
		a->push( s );
	}
	for( int i = 0; i < 15; i++ )
	{
		if( a->peek() != NULL ) cout << a->peek()->todo << endl;
		a->pop();
	}
	return 0;
}