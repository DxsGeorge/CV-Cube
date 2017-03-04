#include "MyHash.h"
#include "FaceFinder.h"
#include <vector>

LinkedList::LinkedList()
{
    head = new Item;
    head -> next = NULL;
    length = 0;
}

void LinkedList::insertItem( Item * newItem )
{
    if (!head->next)
    {
        head->next = newItem;
        length++;
        return;
    }
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        q = p -> next;
    }
    p -> next = newItem;
    newItem -> next = NULL;
    length++;
}

bool LinkedList::removeItem( float itemKey )
{
    if (!head -> next) return false;
    Item * p = head;
    Item * q = head;
    while (q)
    {
        if (abs(q -> key - itemKey)<0.1)
        {
            p -> next = q -> next;
            delete q;
            length--;
            return true;
        }
        p = q;
        q = p -> next;
    }
    return false;
}

Item * LinkedList::getItem( float itemKey )
{
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        if ((p != head) && (abs(p -> key - itemKey)<0.3))
            return p;
        q = p -> next;
    }
    return NULL;
}

vector<Item> LinkedList::getAllItems ()
{
	vector<Item> items;
	Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        q = p -> next;
		items.push_back(*p);
    }
	return items;
}

void LinkedList::printList(){};

int LinkedList::getLength()
{
    return length;
}

LinkedList::~LinkedList()
{
	/*
    Item * p = head;
    Item * q = head;
    while (q)
    {
        p = q;
        q = p -> next;
        if (q) delete p;
    }
	*/
}

HashTable::HashTable( int tableLength )
{
    if (tableLength <= 0) tableLength = 13;
    list = new LinkedList[ tableLength ];
    length = tableLength;
}

int HashTable::hash( float key )
{
	int intkey = int(key)%length;
    return intkey;
}

void HashTable::insertItem( Item * newItem )
{
    int index = hash( newItem -> key );
    list[ index ].insertItem( newItem );
}

bool HashTable::removeItem( float key )
{
    int index = hash( key );
    return list[ index ].removeItem( key );
}

Item * HashTable::getItem( float key )
{
    int index = hash( key );
    return list[ index ].getItem( key );
}

void HashTable::printTable()
{
    cout << "\n\nHash Table:\n";
    for ( int i = 0; i < length; i++ )
    {
        cout << "Bucket " << i + 1 << ": ";
        list[i].printList();
    }
}

int HashTable::getLength()
{
    return length;
}

int HashTable::getNumberOfItems()
{
    int itemCount = 0;
    for ( int i = 0; i < length; i++ )
    {
        itemCount += list[i].getLength();
    }
    return itemCount;
}

HashTable::~HashTable()
{
    delete [] list;
}

