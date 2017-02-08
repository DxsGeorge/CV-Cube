#include "FaceFinder.h"

vector<Point> FindIntersectionSpots (vector<Line> lines, int p_offset, float l_offset)
{
	vector <Point> SamePoints;
//remove same lines
	/*
	for (size_t i=0; i<lines.size(); i++)
	{
		Line l(lines[i].x1,lines[i].y1,lines[i].x2,lines[i].y2);
		lines.erase(remove_if(lines.begin()+i, lines.end(),[&l,s_offset,l_offset] (Line &other) {return l.same_as(other,s_offset,l_offset);}));
	}
	*/
	for( size_t i = 0; i < lines.size(); i++ )
    {
		
		for (size_t j = i+1; j < lines.size(); j++)
		{
 //vertical lines
			if (VerticalLines(lines[i],lines[j],l_offset))
			{
 //only start points
				Point A=Point(lines[i].x1,lines[i].y1);
				Point B=Point(lines[i].x2,lines[i].y2);
				Point C=Point(lines[j].x1,lines[j].y1);
				Point D=Point(lines[j].x2,lines[j].y2);
				if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x1,lines[j].y1),p_offset)||
					SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),p_offset))
				{
					SamePoints.push_back(Point(lines[j].x1,lines[j].y1));
					break;
				}
				else if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x2,lines[j].y2),p_offset)||
						SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x2,lines[j].y2),p_offset)) 
				{
					SamePoints.push_back(Point(lines[j].x2,lines[j].y2));
					break;
				}
			
	// intersections
				Point a;
				if(LineIntersection2(A, B, C, D, a)) SamePoints.push_back(a);			
			}
		}
	}
	return SamePoints;
}

vector<Point> FindSquares(vector <Point> points)
{
	vector<Point> squares;
	for (size_t i=0;i<points.size();i++)
	{
		for (size_t j=i+1;j<points.size();j++)
		{
			float dist=Distance(points[i],points[j]);

		}
	}
	return squares;
}
