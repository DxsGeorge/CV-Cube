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
		
		for (size_t j = i; j < lines.size(); j++)
		{
			if (i!=j && VerticalLines(Point(lines[i].x1,lines[i].y1),Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),Point(lines[j].x2,lines[j].y2),l_offset))
			{
 //only start points
				if ((SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x1,lines[j].y1),p_offset)||
					SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),p_offset)) &&
					i != j)
				{
					SamePoints.push_back(Point(lines[j].x1,lines[j].y1));
				}
				else if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x2,lines[j].y2),p_offset)||
						SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x2,lines[j].y2),p_offset) &&
						i != j) 
				{
					SamePoints.push_back(Point(lines[j].x2,lines[j].y2));
				}
 // intersections
				Point a;
				if (LineIntersection(lines[i].x1,lines[i].y1,lines[i].x2,lines[i].y2,lines[j].x1,lines[j].y1,lines[j].x2,lines[j].y2, a))
				{
					SamePoints.push_back(a);
				}
			}
		}
	}
	return SamePoints;
}