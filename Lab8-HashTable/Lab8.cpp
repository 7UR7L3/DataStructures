#include "Lab8.hpp"

//Hash Function
int HashTab::HashFunc(int key)
{
    return key;
}

//insert an element in HashTable
void HashTab::Insert(int key)
{
    int index = HashFunc( key ) % TABLE_SIZE;
    Node* n = htable[ index ];
    Node* newFront = new Node( key );
    newFront->next = n;
    htable[ index ] = newFront;
}

//Display HashTable
void HashTab::display()
{
    for( int i = 0; i < TABLE_SIZE; i++ )
    {
        cout << i << ": ";
        for( Node* n = htable[i]; n != NULL; n = n->next )
            cout << n->key << " -> ";
        cout << endl;
    }

}
  
//Search an element.  
int HashTab::Find(int key)
{
    int index = HashFunc( key ) % TABLE_SIZE;
    for( Node* n = htable[ index ]; n != NULL; n = n->next ) if( n->key == key ) return index;
    return -1;
}
   
// Delete an Element
void HashTab::Delete(int key)
{
    int index = HashFunc( key ) % TABLE_SIZE;
    if( htable[ index ] == NULL ) return;
    if( htable[index]->key == key )
    {
        Node* toDel = htable[index];
        htable[index] = htable[index]->next;
        delete toDel;
        return;
    }
    Node* n = htable[ index ];
    for( ; n->next != NULL && n->next->key != key; n = n->next );
    Node* toDel = n->next;
    if( n->next != NULL ) n->next = n->next->next;
    delete toDel;
}

int main()
{
    int size = 10, element, ch, hash_val;
    HashTab hash(10);
    while(1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search an element "<<endl;
        cout<<"3.Delete element "<<endl;
        cout<<"4.Display HashTable"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch)
        {
        case 1:
            cout<<"Enter element to be inserted: ";
            cin>>element;
            hash.Insert(element);
            break;
        case 2:
            cout<<"Enter the element to be searched: ";
            cin>>element;
            hash_val = hash.HashFunc(element);
            if (hash.Find(element) == -1)
            cout<<"No element found at key "<<element<<endl;
            else
            {
                cout<<"Element found at index "<<hash_val<<" : ";
                cout<<"position "<<hash.Find(element)<<endl;
            }
            break;
        case 3:
            cout<<"Enter the element to be deleted: ";
            cin>>element;
            if (hash.Find(element) == -1)
                cout<<"Key "<<element<<" is empty, nothing to delete"<<endl;
            else
            {
                hash.Delete(element);
                cout<<"Entry Deleted"<<endl;
            }
            break;
        case 4:
               hash.display();
               break;      
        case 5:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}