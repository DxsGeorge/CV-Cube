#pragma once

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <unordered_set>
#include <array>

using namespace cv;
using namespace std;

class Line 
{
	public: 
		int x1,x2,y1,y2;
		Line(int x1,int y1,int x2,int y2);
		Line(Point p1, Point p2);
		Line();
		bool same_as(Line l,int offset1, float offset2);
		float length();
		Point getPoint(int x);

};

float absDifference(Point p1, Point p2);

bool SamePoint (Point p1, Point p2, int offset);

bool VerticalLines (Point p1, Point p2, Point p3, Point p4, float offset);

bool VerticalLines (Line l1, Line l2, float offset);

bool PerpLines(Line l1, Line l2, float offset);

float Distance (int x1, int y1, int x2, int y2);

float Distance (Point p1, Point p2);

float Distance(Line l1, Line l2);

float twoDcross (float x1, float y1, float x2, float y2);

bool LineIntersection (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Point &a);

bool sameLine (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,int offset1, float offset2);

bool CounterClockWise(Point a, Point b, Point c);

bool LineIntersection2(Point a, Point b, Point c, Point d, Point &r);

Point IntersectionPoint(Point a, Point b, Point c, Point d);

bool intersection2(Point A1, Point A2, Point B1, Point B2, Point &P);

bool intersection3(Point A, Point B, Point C, Point D);

bool intersection3(Point A, Point B, Point C, Point D, Point &P);

bool CheckParallel(Point a, Point b, Point c, Point d);

bool CheckParallel(Line l1, Line l2);

bool isBetween(Point a, Point b, Point c);

bool isBetween2(Point a, Point b, Point c);

bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,Point &r);

bool SameLine(Line l1, Line l2, float offset);


class Square
{
	Point p1, p2, p3, p4;
public:
	Square (Point point1, Point point2, Point point3, Point point4);
	float Area();
	Point getPoint(int val);
	bool operator==(Square x);
	Point getCenter();
	float sideSize();
	float diagSize();
};

bool isSquare(array<Point,2> p12, array<Point,2> p34, float dist, float offset);

bool isSquare(array<Line,2> l12, array<Line,2> l34, float offset);

bool isSquare2(Point p1[3], Point p2[3],float distance1, float distance2, float offset);

bool PointsInLine(Point a, Point b, Point c);