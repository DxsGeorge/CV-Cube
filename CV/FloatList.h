#pragma once

#include <stddef.h>
#include "Line.h"

class Node
{
private:
	Point p1,p2;
	float distance;
	Node* next;

public:
	Node(void);

	Node(Point point1, Point point2);

	Node(Point point1, Point point2, Node* next);

	Point getPoint1(void);

	Point getPoint2(void);

	float getDistance(void);

	Node* getNext(void);

};

class PointList
{
private:
	Node* head;
	Node* tail;
	int length;

public:
	PointList(void);

	PointList(float val);

	void traverse();

	void addItem(Point p1, Point p2);

	int getLength();

};

