#include "Line.h"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

float eps=std::numeric_limits<float>::epsilon();
double epsilon=0.001;

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

Line::Line()
{

}

Line::Line(Point p1, Point p2)
{
	Line(p1.x,p1.y,p2.x,p2.y);
}

Point Line::getPoint(int x)
{
	switch (x)
	{
	case 1:
		return Point(x1,y1);
		break;
	case 2:
		return Point(x2,y2);
		break;
	default:
		return Point(NULL,NULL);
		break;
	}
}

float Line::length()
{
	return sqrt(pow(float(x1-x2),2)+pow(float(y1-y2),2));
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
	return (abs(p1.x-p2.x)<offset && abs(p1.y-p2.y)<offset);
}

float absDifference(Point p1, Point p2)
{
	return ((abs(p1.x-p2.x)+abs(p1.y-p2.y))/2.0);
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

bool PerpLines(Line l1, Line l2, float offset)
{
	int dot=(l1.x1-l1.x2)*(l2.x1-l2.x2)+(l1.y1-l1.y2)*(l2.y1-l2.y2);
	return (dot<offset*1000);
}

float Distance (int x1, int y1, int x2, int y2)
{
	float abs1=pow(float (x1-x2),2)+pow(float (y1-y2),2);
	float dist=sqrt(abs1);
	return dist;
}

float Distance (Point p1, Point p2)
{
	return Distance(p1.x,p1.y,p2.x,p2.y);
}

float Distance(Line l1, Line l2)
{
	return Distance(int(l1.x1+l1.x2/2),int(l1.y1+l1.y2/2),int(l2.x1+l2.x2/2),int(l2.y1+l2.y2/2));
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

bool CounterClockWise(Point a, Point b, Point c)
{
	return (c.y-a.y)*(b.x-a.x) > (b.y-a.y)*(c.x-a.x);
}

bool LineIntersection2(Point A, Point B, Point C, Point D, Point &r)
{
	Point2f s1,s2;
	s1=B-A;
    s2=D-C;
	float s, t;
	if ( abs(-s2.x * s1.y + s1.x * s2.y)<=eps) return false;
    s = (-s1.y * (A.x - C.x) + s1.x * (A.y - C.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = ( s2.x * (A.y - C.y) - s2.y * (A.x - C.x)) / (-s2.x * s1.y + s1.x * s2.y);
	if (s>=epsilon && s -1 <= epsilon && t >= epsilon && t - 1 <= epsilon)
    {
        // Collision detected
        r.x = A.x + (t * s1.x);
        r.y = A.y + (t * s1.y);
        return true;
    }

    return false; // No collision

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

bool CheckParallel(Point a, Point b, Point c, Point d)
{
	return (abs((a.x-b.x)*(c.y-d.y)-(a.y-b.y)*(c.x-d.x))<0.01 );
}

bool CheckParallel(Line l1, Line l2)
{
	return CheckParallel(Point(l1.x1,l1.y1),Point(l1.x2,l1.y2),Point(l2.x1,l2.y1),Point(l2.x2,l2.y2));
}

Point IntersectionPoint(Point a, Point b, Point c, Point d)
{
	float X=(float)((a.x*b.y-a.y*b.x)*(c.x-d.x)-(a.x-b.x)*(c.x*d.y-d.x*c.y))/((a.x-b.x)*(c.y-d.y)-(a.y-b.y)*(c.x-d.x));
	float Y=(float)((a.x*b.y-a.y*b.x)*(c.y-d.y)-(a.y-b.y)*(c.x*d.y-d.x*c.y))/((a.x-b.x)*(c.y-d.y)-(a.y-b.y)*(c.x-d.x));
	return Point((int) X, (int) Y);
}

bool isBetween(Point a, Point b, Point c)
{
	float crossproduct = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
	float dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y)*(b.y - a.y);
	float squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
	if (abs(crossproduct)<std::numeric_limits<float>::epsilon()) return false;
	
    else if (abs(dotproduct) < std::numeric_limits<float>::epsilon())  return false;
	
    else if (dotproduct > squaredlengthba) return false;

    else return true;
}

bool isBetween2(Point a, Point b, Point c)
{
	float ba = sqrt((float)(b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
	float bc = sqrt((float)(b.x - c.x)*(b.x - c.x) + (b.y - c.y)*(b.y - c.y));
	float ac = sqrt((float)(c.x - a.x)*(c.x - a.x) + (c.y - a.y)*(c.y - a.y));
	return (abs(ac+bc-ba)<std::numeric_limits<double>::epsilon()); 
}

bool SameLine(Line l1, Line l2, float offset)
{
	if (((abs(l1.x1-l2.x1)<offset && abs(l1.y1-l2.y1)<offset) && (abs(l1.x2-l2.x2)<offset && abs(l1.y2-l2.y2)<offset)) ||
		((abs(l1.x1-l2.x2)<offset && abs(l1.y1-l2.y2)<offset) && (abs(l1.x2-l2.x1)<offset && abs(l1.y2-l2.y1)<offset)) ) return true;
	else return false;

}

bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,Point &r)
{
    Point2f x = o2 - o1;
    Point2f d1 = p1 - o1;
    Point2f d2 = p2 - o2;

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (abs(cross) < std::numeric_limits<double>::epsilon())
        return false;

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return true;
}

bool intersection2(Point A1, Point A2, Point B1, Point B2, Point &P)
{
	Point A;
	A.x=A1.x-A2.x;
	A.y=A1.y-A2.y;
	Point B;
	B.x=B1.x-B2.x;
	B.y=B1.y-B2.y;
	double f=(A.y*B.x) - (A.x*B.y);
	if(!f) return false;
	Point C;
	C.x=B2.x-A2.x;
	C.y=B2.y-A2.y;
	double aa = (A.y*C.x) - (A.x*C.y);
	double bb = (B.y*C.x) - (B.x*C.y);
	 if(f < 0)
    {
        if(aa > 0)     return false;
        if(bb > 0)     return false;
        if(aa < f)     return false;
        if(bb < f)     return false;
    }
    else
    {
        if(aa < 0)     return false;
        if(bb < 0)     return false;
        if(aa > f)     return false;
        if(bb > f)     return false;
    }
	P.x = ((B2.x - B1.x) * (1.0 - (aa / f))) + B1.x;
	P.y = ((B2.y - B1.y) * (1.0 - (aa / f))) + B1.y;
	return true;
}

bool intersection3(Point A, Point B, Point C, Point D, Point &P)
{
	if (A.x==C.x && A.y==C.y || B.x==C.x && B.y==C.y ||  A.x==D.x && A.y==D.y || B.x==D.x && B.y==D.y) return false;
	double  distAB, theCos, theSin, newX, ABpos ;
	B.x-=A.x; B.y-=A.y;
	C.x-=A.x; C.y-=A.y;
	D.x-=A.x; D.y-=A.y;
	distAB=sqrt(float(B.x*B.x+B.y*B.y));
	theCos=B.x/distAB;
	theSin=B.y/distAB;
	newX=C.x*theCos+C.y*theSin;
	C.y=C.y*theCos-C.x*theSin; 
	C.x=newX;
	newX=D.x*theCos+D.y*theSin;
	D.y=D.y*theCos-D.x*theSin; 
	D.x=newX;
	if (C.y<0. && D.y<0. || C.y>=0. && D.y>=0.) return false;
	ABpos=D.x+(C.x-D.x)*D.y/(D.y-C.y);
	if (ABpos<0. || ABpos>distAB) return false;
	P.x=A.x+ABpos*theCos;
	P.y=A.y+ABpos*theSin;
	return true;
}

bool intersection3(Point A, Point B, Point C, Point D)
{
	Point a;
	return intersection3(A, B, C, D, a);
}

Square::Square (Point point1, Point point2, Point point3, Point point4)
{
	p1=point1;
	p2=point2;
	p3=point3;
	p4=point4;
}

float Square::Area()
{
	return pow(Distance(p1,p2),2);
}

Point Square::getPoint(int val)
{
	switch (val) {
	case 1: 
		return this->p1;
		break;
	case 2:
		return this->p2;
		break;
	case 3:
		return this->p3;
		break;
	case 4:
		return this->p4;
		break;
	default:
		return Point(NULL);
		break;
	}
}

Point Square::getCenter()
{
	if (Distance(this->getPoint(1),this->getPoint(2))/Distance(this->getPoint(1),this->getPoint(3))<1.3)
		return Point(int((this->getPoint(1).x-this->getPoint(2).x)/2),int((this->getPoint(1).y-this->getPoint(2).y)/2));
	else 
		return Point(int((this->getPoint(1).x+this->getPoint(3).x)/2),int((this->getPoint(1).y+this->getPoint(3).y)/2));
}

float Square::sideSize()
{
	float min1=min(Distance(this->getPoint(1),getPoint(2)),Distance(this->getPoint(2),getPoint(3)));
	float min2=min(Distance(this->getPoint(1),getPoint(2)),Distance(this->getPoint(1),getPoint(3)));
	return min(min1,min2);
}

float Square::diagSize()
{
	float max1=max(Distance(this->getPoint(1),getPoint(2)),Distance(this->getPoint(2),getPoint(3)));
	float max2=max(Distance(this->getPoint(1),getPoint(2)),Distance(this->getPoint(1),getPoint(3)));
	return max(max1,max2);
}

bool Square::operator==(Square x)
{
	return (abs(this->getCenter().x-x.getCenter().x)<5 && abs(this->getCenter().y-x.getCenter().y)<5);
}

bool isSquare(array<Point,2> p12, array<Point,2> p34, float dist, float offset)
{
	Point p1=p12[0];
	Point p2=p12[1];
	Point p3=p34[0];
	Point p4=p34[1];
	if (abs((Distance(p1,p3)-dist)<offset && abs(Distance(p2,p4)-dist)<offset) ||
		abs(Distance(p1,p4)-dist)<offset && abs(Distance(p2,p3)-dist)<offset)
	{
		return true;
	}
	else return false;
}

bool isSquare(array<Line,2> l12, array<Line,2> l34, float offset)
{
	if (SameLine(l12[0],l34[0],offset) || SameLine(l12[0],l34[1],offset) || SameLine(l12[1],l34[0],offset) || SameLine(l12[1],l34[1],offset)) return false;
	if (abs(l12[0].x1-l12[1].x1)<offset && abs(l12[0].y1-l12[1].y1)<offset)
	{
		if (abs(l34[0].x1-l34[1].x1)<offset && abs(l34[0].y1-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset) && (abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset)) ||
					((abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset) && (abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset) && (abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset) && (abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x1)<offset && abs(l34[0].y2-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset) && (abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset)) ||
					((abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset) && (abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset) && (abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset) && (abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset)));
		}
		else if (abs(l34[0].x1-l34[1].x2)<offset && abs(l34[0].y1-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset) && (abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset)) ||
					((abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset) && (abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset) && (abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset) && (abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x2)<offset && abs(l34[0].y2-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset) && (abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset)) ||
					((abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset) && (abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset) && (abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset) && (abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset)));
		}
	}
	else if (abs(l12[0].x1-l12[1].x2)<offset && abs(l12[0].y1-l12[1].y2)<offset)
	{
		if (abs(l34[0].x1-l34[1].x1)<offset && abs(l34[0].y1-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset) && (abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset)) ||
					((abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset) && (abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset) && (abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset) && (abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x1)<offset && abs(l34[0].y2-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset) && (abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset)) ||
					((abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset) && (abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset) && (abs(l12[0].x2-l34[0].x2)<offset && abs(l12[0].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset) && (abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset)));
		}
		else if (abs(l34[0].x1-l34[1].x2)<offset && abs(l34[0].y1-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset) && (abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset)) ||
					((abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset) && (abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset) && (abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset) && (abs(l12[0].x2-l34[1].x2)<offset && abs(l12[0].y2-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x2)<offset && abs(l34[0].y2-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset) && (abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset)) ||
					((abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset) && (abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset) && (abs(l12[0].x2-l34[0].x1)<offset && abs(l12[0].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset) && (abs(l12[0].x2-l34[1].x1)<offset && abs(l12[0].y2-l34[1].y1)<offset)));
		}
	}
	else if (abs(l12[0].x2-l12[1].x1)<offset && abs(l12[0].y2-l12[1].y1)<offset)
	{
		if (abs(l34[0].x1-l34[1].x1)<offset && abs(l34[0].y1-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset) && (abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset)) ||
					((abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset) && (abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset) && (abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset) && (abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x1)<offset && abs(l34[0].y2-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset) && (abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset)) ||
					((abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset) && (abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset) && (abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x2-l34[0].x2)<offset && abs(l12[1].y2-l34[0].y2)<offset) && (abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset)));
		}
		else if (abs(l34[0].x1-l34[1].x2)<offset && abs(l34[0].y1-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset) && (abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset)) ||
					((abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset) && (abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[1].x2)<offset && abs(l12[1].y2-l34[1].y2)<offset) && (abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset) && (abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x2)<offset && abs(l34[0].y2-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset) && (abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset)) ||
					((abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset) && (abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[1].x1)<offset && abs(l12[1].y2-l34[1].y1)<offset) && (abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x2-l34[0].x1)<offset && abs(l12[1].y2-l34[0].y1)<offset) && (abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset)));
		}
	}
	else if (abs(l12[0].x2-l12[1].x2)<offset && abs(l12[0].y2-l12[1].y2)<offset)
	{
		if (abs(l34[0].x1-l34[1].x1)<offset && abs(l34[0].y1-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset) && (abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset)) ||
					((abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset) && (abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset) && (abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset) && (abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x1)<offset && abs(l34[0].y2-l34[1].y1)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset) && (abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset)) ||
					((abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset) && (abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset) && (abs(l12[0].x1-l34[0].x2)<offset && abs(l12[0].y1-l34[0].y2)<offset)) ||
					((abs(l12[1].x1-l34[0].x2)<offset && abs(l12[1].y1-l34[0].y2)<offset) && (abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset)));
		}
		else if (abs(l34[0].x1-l34[1].x2)<offset && abs(l34[0].y1-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset) && (abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset)) ||
					((abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset) && (abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[1].x2)<offset && abs(l12[1].y1-l34[1].y2)<offset) && (abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset) && (abs(l12[0].x1-l34[1].x2)<offset && abs(l12[0].y1-l34[1].y2)<offset)));
		}
		else if (abs(l34[0].x2-l34[1].x2)<offset && abs(l34[0].y2-l34[1].y2)<offset)
		{
			return (((abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset) && (abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset)) ||
					((abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset) && (abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[1].x1)<offset && abs(l12[1].y1-l34[1].y1)<offset) && (abs(l12[0].x1-l34[0].x1)<offset && abs(l12[0].y1-l34[0].y1)<offset)) ||
					((abs(l12[1].x1-l34[0].x1)<offset && abs(l12[1].y1-l34[0].y1)<offset) && (abs(l12[0].x1-l34[1].x1)<offset && abs(l12[0].y1-l34[1].y1)<offset)));
		}
	}
}

bool isSquare2(Point p1[3], Point p2[3],float distance1, float distance2, float offset)
{
	if (max(distance1,distance2)/min(distance1,distance2)>1.3) return false;
	if (abs(p1[0].x-p2[0].x)<0.1 && abs(p1[0].y-p2[0].y)<0.1) return false;
	if ((abs(p1[1].x-p2[1].x)<offset && abs(p1[1].y-p2[1].y)<offset && (abs(p1[2].x-p2[2].x)<offset && abs(p1[2].y-p2[2].y)<offset)) ||
		(abs(p1[1].x-p2[2].x)<offset && abs(p1[1].y-p2[2].y)<offset && (abs(p1[2].x-p2[1].x)<offset && abs(p1[2].y-p2[1].y)<offset)))
		return true;
	else return false;
}

bool PointsInLine(Point a, Point b, Point c)
{
	return ((max(abs(b.y-a.y)*(c.x-b.x),abs((c.y-b.y)*(b.x-a.x))))/(min(abs(b.y-a.y)*(c.x-b.x),abs((c.y-b.y)*(b.x-a.x))))<1.3);
}