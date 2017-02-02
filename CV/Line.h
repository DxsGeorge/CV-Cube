#pragma once
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <unordered_set>

using namespace cv;
using namespace std;

class Line 
{
	public: 
		int x1,x2,y1,y2;
		Line(int x1,int y1,int x2,int y2);
		bool same_as(Line l,int offset1, float offset2);

};

bool SamePoint (Point p1, Point p2, int offset);

bool VerticalLines (Point p1, Point p2, Point p3, Point p4, float offset);

bool VerticalLines (Line l1, Line l2, float offset);

float Distance (int x1, int y1, int x2, int y2);

float twoDcross (float x1, float y1, float x2, float y2);

bool LineIntersection (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Point &a);

bool sameLine (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,int offset1, float offset2);

bool CounterClockWise(Point a, Point b, Point c);

bool LineIntersection2(Point a, Point b, Point c, Point d, Point &r);

Point IntersectionPoint(Point a, Point b, Point c, Point d);

bool CheckParallel(Point a, Point b, Point c, Point d);

bool isBetween(Point a, Point b, Point c);

bool isBetween2(Point a, Point b, Point c);

bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,Point &r);

