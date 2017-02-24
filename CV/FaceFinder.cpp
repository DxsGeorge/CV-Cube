#include "FaceFinder.h"

float roundf(float val)
{
	return val >= 0.0f ? floorf(val + 0.5f) : ceilf(val - 0.5f);
}

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

vector<Square> FindSquares(vector <Point> points, float offset)
{
	vector<Square> squares;
	multimap<float, array<Point,2>> distances;
	for (size_t i=0;i<points.size();i++)
	{
		for (size_t j=i+1;j<points.size();j++)
		{
			float dist=Distance(points[i],points[j]);
			dist=roundf(dist);
			array<Point,2> pointa;
			pointa[0]=points[i];
			pointa[1]=points[j];
			distances.insert(pair<float,array<Point,2>>(dist,pointa));
		}
	}
	for (multimap<float, array<Point,2>>::iterator it = distances.begin(); it!=distances.end(); ++it)
	{
		float dist = (*it).first;
		if  (distances.count(dist)<4) break;
		pair<multimap<float,array<Point,2>>::iterator,multimap<float,array<Point,2>>::iterator> range = distances.equal_range(dist);
		for (multimap<float, array<Point,2>>::iterator it2 = range.first; it2!=range.second ; ++it2)
		{
			if (isSquare((*it).second,(*it2).second,(*it).first,offset)) 
				squares.push_back(Square((*it).second[0],(*it).second[1],(*it2).second[0],(*it2).second[1]));
		}
	}
	return squares;
}

vector<Square> FindSquares(vector <Line> lines, int p_offset, float l_offset)
{
	vector<Square> squares;
	multimap<float, array<Line,2>> line_pairs;
	for (size_t i=0;i<lines.size();i++)
	{
		for (size_t j=i+1;j<lines.size();j++)
		{
			if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x1,lines[j].y1),p_offset) ||
				SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x2,lines[j].y2),p_offset) ||
				SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),p_offset) ||
				SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x2,lines[j].y2),p_offset) )
			{
				if (VerticalLines(lines[i],lines[j],l_offset))
				{
					array<Line,2> line_a;
					line_a[0]=lines[i];
					line_a[1]=lines[j];
					line_pairs.insert(pair<float,array<Line,2>>(lines[i].length(),line_a));
				}
			}

		}
	}
	for (multimap<float, array<Line,2>>::iterator it = line_pairs.begin(); it!=line_pairs.end(); ++it)
	{
		float dist = (*it).first;
		pair<multimap<float,array<Line,2>>::iterator,multimap<float,array<Line,2>>::iterator> range = line_pairs.equal_range(dist);
		for (multimap<float, array<Line,2>>::iterator it2 = range.first; it2!=range.second ; ++it2)
		{
			if (isSquare((*it).second,(*it2).second,l_offset))
			squares.push_back(Square(Point((*it).second[0].x1,(*it).second[0].y1),
							         Point((*it).second[1].x1,(*it).second[1].y1),
							         Point((*it2).second[0].x1,(*it).second[0].y1),
							         Point((*it2).second[1].x1,(*it).second[1].y1)));
		}
	}
	return squares;
}