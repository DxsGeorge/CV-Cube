#include "Line.h"
#include <math.h>

using namespace cv;
using namespace std;

Line::Line(int x1,int y1,int x2,int y2)
{
	if (y1>y2)
	{
		this->x1=x1;
		this->x2=x2;
		this->y1=y1;
		this->y2=y2;
	}
	else
	{
		this->x1=x2;
		this->x2=x1;
		this->y1=y2;
		this->y2=y1;
	}
}

bool Line::same_as(Line l,int offset1, float offset2)
{
	int dot=(x1-x2)*(l.x1-l.x2)+(y1-y2)*(l.y1-l.y2);
	float abs1=pow(float (x1-x2),2)+pow(float (y1-y2),2);
	float abs2=pow(float (l.x1-l.x2),2)+pow(float (l.y1-l.y2),2);
	float abs_values=sqrt(abs1)*sqrt(abs2);
	float cosf=dot/abs_values;
	if (abs(x1-l.x1)<offset1 && abs(y1-l.y1)<offset1 && abs(x2-l.x2)<offset1 && abs(y2-l.y2)<offset1) return true;
	else if (abs(x1-l.x1)<offset1 && abs(y1-l.y1)<offset1 && abs(cosf-1)<offset2) return true;
	else if (abs(x2-l.x2)<offset1 && abs(y2-l.y2)<offset1 && abs(cosf-1)<offset2) return true;
	else return false;
}

bool SamePoint (Point p1, Point p2, int offset) 
{
	if (abs(p1.x-p2.x)<offset && abs(p1.y-p2.y)<offset) return true;
	else return false;
}

bool VerticalLines (Point p1, Point p2, Point p3, Point p4, float offset)
{
	int dot=(p1.x-p2.x)*(p3.x-p4.x)+(p1.y-p2.y)*(p3.y-p4.y);
	float abs1=pow(float (p1.x-p2.x),2)+pow(float (p1.y-p2.y),2);
	float abs2=pow(float (p3.x-p4.x),2)+pow(float (p3.y-p4.y),2);
	float abs_values=sqrt(abs1)*sqrt(abs2);
	float cosf=dot/abs_values;
	if (abs(cosf)<offset) return true;
	else return false;
}

bool VerticalLines (Line l1, Line l2, float offset)
{
	Point p1(l1.x1,l1.y1);
	Point p2(l1.x2,l1.y2);
	Point p3(l2.x1,l2.y1);
	Point p4(l2.x2,l2.y2);
	int dot=(p1.x-p2.x)*(p3.x-p4.x)+(p1.y-p2.y)*(p3.y-p4.y);
	float abs1=pow(float (p1.x-p2.x),2)+pow(float (p1.y-p2.y),2);
	float abs2=pow(float (p3.x-p4.x),2)+pow(float (p3.y-p4.y),2);
	float abs_values=sqrt(abs1)*sqrt(abs2);
	float cosf=dot/abs_values;
	if (abs(cosf)<offset) return true;
	else return false;
}

float Distance (int x1, int y1, int x2, int y2)
{
	float abs1=pow(float (x1-x2),2)+pow(float (y1-y2),2);
	float dist=sqrt(abs1);
	return dist;
}

float twoDcross (float x1, float y1, float x2, float y2)
{
	return x1*y2-y1*x2;
}

bool LineIntersection (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Point &a)
{
	//p = x1 y1, q = x3 y3, r = x2 y2, s = x4 y4
	//t = (q − p) × s / (r × s)
	float t=twoDcross(x3-x1,y3-y1,(x4-x3)/twoDcross(x2-x1,y2-y1,x4-x3,y4-y3),(y4-y3)/twoDcross(x2-x1,y2-y1,x4-x3,y4-y3));
	//u = (q − p) × r / (r × s)
	float u=twoDcross(x3-x1,y3-y1,(x2-x1)/twoDcross(x2-x1,y2-y1,x4-x3,y4-y3),y2/twoDcross(x2-x1,y2-y1,x4-x3,y4-y3));
	//r × s ≠ 0 and 0 ≤ t ≤ 1 and 0 ≤ u ≤ 1
	if (twoDcross(x2-x1,y2-y1,x4-x3,y4-y3)!=0 && t>=0 && t<=1 && u>=0 && u<=1) 
	{
			a=Point(int(x1+t*(x2-x1)),int(y1+t*(y2-y1)));
			return true;
	}
	else return false;
}

bool sameLine (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,int offset1, float offset2) 
{
	int dot=(x1-x2)*(x3-x4)+(y1-y2)*(y3-y4);
	float abs1=pow(float (x1-x2),2)+pow(float (y1-y2),2);
	float abs2=pow(float (x3-x4),2)+pow(float (y3-y4),2);
	float abs_values=sqrt(abs1)*sqrt(abs2);
	float cosf=dot/abs_values;
	if (abs(x1-x3)<offset1 && abs(y1-y3)<offset1 && abs(x2-x4)<offset1 && abs(y2-y4)<offset1) return true;
	else if (abs(x1-x3)<offset1 && abs(y1-y3)<offset1 && abs(cosf-1)<offset2) return true;
	else if (abs(x2-x4)<offset1 && abs(y2-y4)<offset1 && abs(cosf-1)<offset2) return true;
	else return false;
}