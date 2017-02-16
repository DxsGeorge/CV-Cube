#include "FloatList.h"

class Node
{
private:
	Point p1,p2;
	float distance;
	Node* next;

public:
	Node(void):next(){};

	Node(Point point1, Point point2):p1(point1), p2(point2), next(NULL){ };

	Node(Point point1, Point point2, Node* next):p1(point1), p2(point2), next(next){};

	Point getPoint1(void)
	{
		return p1;
	};

	Point getPoint2(void)
	{
		return p1;
	};

	float getDistance(void)
	{
		return distance;
	};

	Node* getNext(void)
	{
		return next;
	};

};

class PointList
{
private:
	Node* head;
	Node* tail;
	int length;

public:
	PointList(void)
	{
		head=tail=NULL;
		length=0;
	};

	PointList(Point p1, Point p2)
	{
		head=new Node(p1,p2);
		tail=head;
		length=1;
	};

	void traverse()
	{

	};

	void addItem(Point p1, Point p2)
	{
		Node newnode(p1, p2, head);
		*head=newnode;
		length++;
	};

	int getLength()
	{
		return length;
	}

};