// ==========================================
// File: Homework 2
// Author: Michael Rahn
// Date: 9/22/2016
// Modified: Fall 2016 E.S.Boese
// Description: Linked List Fun
// ==========================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct city
{
    string 	name; 			// name of the city
    city 	*next; 			// pointer to the next city
	int 	numberMessages;	// how many messages passed through this city
    string 	message; 		// message we are sending accross
};

city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string filename);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
    // pointer to the head of our network of cities
    city *head = NULL;

	head = handleUserInput(head);
	printPath(head);
	head = deleteEntireNetwork(head);
	if (head == NULL)
		cout << "Path cleaned" << endl;
	else
		printPath(head);

	cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head the start of the linked list
 * @return the start of the linked list
 * Do NOT modify
 */
city* handleUserInput(city *head)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

		// read in input, assuming a number comes in
        getline(cin, s_input);
		input = stoi(s_input);

        switch (input)
        {
            // print all nodes
            case 1: 	//rebuild network
                head = loadDefaultSetup(head);
                printPath(head);
                break;

            case 2:		// print path
                printPath(head);
                break;

            case 3: //message is read in from file
			  {
        		string cityReceiver;
				cout << "Enter name of the city to receive the message: " << endl;
				getline(cin, cityReceiver);

				cout << "Enter the message to send: " << endl;
				string message;
				getline(cin, message);

                transmitMsg(head, cityReceiver, message);
			  }
                break;

            case 4:
			  {
        		string newCityName;
        		string prevCityName;
                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);

                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);

                // find the node containing prevCity
    			city *tmp = NULL;
                if(prevCityName !="First")
                    tmp = searchNetwork(head, prevCityName);
                // add the new node
                head = addCity(head, tmp, newCityName);
                printPath(head);
			  }
                break;

            case 5: 	// delete city
			  {
        		string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                head = deleteCity(head, city);
                printPath(head);
			  }
                break;

            case 6: 	// delete network
                head = deleteEntireNetwork(head);
                break;

            case 7: 	// quit
                quit = true;
				cout << "Quitting... cleaning up path: " << endl;
                break;

            default: 	// invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
	return head;
}

/* 
 * Purpose: Add a new city to the network 
 *   between the city *previous and the city that follows it in the network. 
 * @param head pointer to start of the list
 * @param previous name of the city that comes before the new city
 * @param cityName name of the new city
 * @return pointer to first node in list
 */
city* addCity(city *head, city *previous, string cityName )
{
    //  makes the new node
    city* n = new city();
    n->next = NULL;
    n->numberMessages = 0;
    n->message = "";
    n->name = cityName;

    //  makes that new node the head if the list has no nodes yet
    if( head == NULL || previous == NULL ) return n;
    
    //  inserts the node into the proper slot otherwise
    n->next = previous->next;
    previous->next = n;

    //  prints
	cout << "prev: " << previous->name << "  new: " << cityName << endl;

    return head;
}


/*
 * Purpose: Search the network for the specified city and return a pointer to that node
 * @param ptr head of the list
 * @param cityName name of the city to look for in network
 * @return pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city *searchNetwork(city *ptr, string cityName)
{
    //  iterates until it hits NULL or the node it was searching for and returns that
    city* c = ptr;
    for( ; c != NULL && c->name != cityName; c = c->next );
    if( c == NULL ) return NULL;
    return c;
}

/*
 * Purpose: deletes all cities in the network starting at the head city. 
 * @param ptr head of list
 * @return NULL as the list is empty
 */
city* deleteEntireNetwork(city *ptr)
{
    if( ptr == NULL ) { cout << "Deleted network" << endl; return NULL; }
    cout << "deleting: " << ptr->name << endl;
    return deleteEntireNetwork( deleteCity( ptr, ptr->name ) );
}

/* sends messages from file */
void transmitMsg(city *head, string receiver, string message)
{
    //  the case where the network is empty
    if(head == NULL)
	{
        cout << "Empty list" << endl;
        return;
    }

    //  start sending the message from head
    city* sender = head;
    sender->message = message;
    //  iterate through to the receiver, setting the message, incrementing the number of messages passed, and printing
    for( ; sender->name != receiver; sender = sender->next )
    {
        sender->next->message = message;
    	cout << sender->name << " [# messages passed: " << ++sender->numberMessages << "] received: " << sender->message << endl;
    }
    //  also do this for the receiver
    cout << sender->name << " [# messages passed: " << ++sender->numberMessages << "] received: " << sender->message << endl;
}


/* 
 * Purpose: delete the city in the network with the specified name. 
 * @param head first node in list
 * @param cityName name of the city to delete in the network
 * @return head node of list 
 */
city* deleteCity(city *head, string cityName)
{
    //  case where the first city is the one to be removed
    if( head->name == cityName )
    {
        city* toRet = head->next;
        delete head;
        return toRet;
    }

    //  the city to find cityName's previous
    city* at = head;

    //  iterate until at is cityName's previous
    for( ; at->next != NULL && at->next->name != cityName; at = at->next );
    
    // if the city dosn't exist, nothing we can do.
    //      use this output statement
    if( at->next == NULL )
    {
        cout << "City does not exist." << endl;
        return head;
    }

    //  delete the next city
    city* toDel = at->next;
    at->next = at->next->next;
    delete toDel;

    //  return the head of the list
    return head;
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void printPath(city *ptr)
{
    cout << "== CURRENT PATH ==" << endl;

    // If the head is NULL
    if (ptr == NULL)
        cout << "nothing in path" << endl;
    else
    {
        for( city* on = ptr; on != NULL; on = on->next ) cout << on->name << " -> ";
        cout << "NULL" << endl;
    }

    cout << "===" << endl;
}

/* 
 * Purpose: populates the network with the predetermined cities 
 * @param head start of list
 * @return head of list
 */
city* loadDefaultSetup(city *head)
{
    head = deleteEntireNetwork(head);
    head = addCity(head,NULL,"Los Angeles");

    addCity( head, head, "Phoenix" );
    addCity( head, head->next, "Denver" );
    addCity( head, head->next->next, "Dallas" );
    addCity( head, head->next->next->next, "Atlanta" );
    addCity( head, head->next->next->next->next, "New York" );

    return head;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
	cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}

