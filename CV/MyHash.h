#pragma once

#include <iostream>
#include "Line.h"

struct Item
{
	float key;
	Point same;
	Point point1;
	Point point2;
	Item* next;
};

class LinkedList
{

private:
	Item* head;
	int length;

public:
	LinkedList();
	void insertItem(Item* newItem);
	bool removeItem(float itemkey);
	Item* getItem(float itemkey);
	vector<Item> getAllItems ();
	void printList();
	int getLength();
	~LinkedList();
};

class HashTable
{
private:
	
	int length;
	int hash(float key);

public:
	LinkedList *list;
	HashTable(int tablelength=100);
	void insertItem(Item * newItem);
	bool removeItem(float key);
	Item* getItem(float key);
	void printTable();
	int getLength();
	int getNumberOfItems();
	~HashTable();
};