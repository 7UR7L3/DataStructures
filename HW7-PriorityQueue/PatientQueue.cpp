#include <string>
#include <iostream>
#include <limits>
#include "PatientQueue.hpp"

PatientQueue::PatientQueue()
{
	lastIndex = -1;
}

//	Releases memory and deletes the queue.
PatientQueue::~PatientQueue()
{
	std::cout << "We're CLOSING! Deleting patient queue!" << std::endl;
	for( int i = 0; i <= lastIndex; i++ )
	{
		std::cout << "Removing " << waitlist[i]->name << " from the queue." << std::endl;
		delete waitlist[i];
	}
}

int PatientQueue::size()
{
	return lastIndex + 1;
}

bool PatientQueue::isEmpty()
{
	return lastIndex == -1;
}

void PatientQueue::enqueue( int priority, std::string name )
{
	std::cout << "Adding " << priority << " " << name << std::endl;

	Patient* toAdd = new Patient( priority, name );
	lastIndex++;
	waitlist[ lastIndex ] = toAdd;
	for( int addingAt = lastIndex; addingAt >= 0 && waitlist[ ( addingAt - 1 ) / 2 ]->priority > priority; addingAt = ( addingAt - 1 ) / 2 )
		swap( ( addingAt - 1 ) / 2, addingAt );

	printList();
}

Patient* PatientQueue::dequeue()
{
	Patient* toRet = waitlist[0];

	std::cout << "Processing " << toRet->priority << " " << toRet->name << std::endl;

	swap( 0, lastIndex );
	lastIndex--;
	for( int siftingAt = 0;; )
	{
		int l = siftingAt * 2 + 1, r = siftingAt * 2 + 2;
		int lv = l > lastIndex ? std::numeric_limits<int>::max() : waitlist[l]->priority,
		    rv = r > lastIndex ? std::numeric_limits<int>::max() : waitlist[r]->priority;

		if( lv == std::numeric_limits<int>::max() && rv == std::numeric_limits<int>::max() ) break;
		swap( siftingAt, lv < rv ? l : r );
		siftingAt = lv < rv ? l : r;
	}

	return toRet;
}

void PatientQueue::printList()
{
	std::cout << "===" << std::endl << "Patients Waiting" << std::endl;
	if( isEmpty() ) std::cout << "No one waiting!" << std::endl;
	for( int i = 0; i <= lastIndex; i++ )
		std::cout << "[" << waitlist[i]->priority << "] " << waitlist[i]->name << std::endl;
	std::cout << "===" << std::endl;
}

//PRIVATE
void PatientQueue::swap( int index1, int index2 )
{
	Patient* t = waitlist[ index1 ];
	waitlist[ index1 ] = waitlist[ index2 ];
	waitlist[ index2 ] = t;

}
