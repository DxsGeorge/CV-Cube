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
			if (lines[i].same_as(lines[j], p_offset, l_offset)) break;
 //vertical lines
			if (PerpLines(lines[i],lines[j],l_offset))
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
				//if(LineIntersection2(A, B, C, D, a)) SamePoints.push_back(a);	
				if(intersection3(A, B, C, D, a)) SamePoints.push_back(a);	
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
	multimap<float, array<Point,3> > points;
	for (size_t i=0;i<lines.size();i++)
	{
		for (size_t j=i+1;j<lines.size();j++)
		{
			if (abs(lines[i].length()-lines[j].length())<0.3)
			{
				if (PerpLines(lines[i],lines[j],l_offset))
				{
					if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x1,lines[j].y1),p_offset)) 
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x1,lines[i].y1);
						points_a[1]=Point(lines[i].x2,lines[i].y2);
						points_a[2]=Point(lines[j].x2,lines[i].y2);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if	(SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x2,lines[j].y2),p_offset)) 
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x1,lines[i].y1);
						points_a[1]=Point(lines[i].x2,lines[i].y2);
						points_a[2]=Point(lines[j].x1,lines[i].y1);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if	(SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),p_offset))
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x2,lines[i].y2);
						points_a[1]=Point(lines[i].x1,lines[i].y1);
						points_a[2]=Point(lines[j].x2,lines[i].y2);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if	(SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x2,lines[j].y2),p_offset)) 
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x2,lines[i].y2);
						points_a[1]=Point(lines[i].x1,lines[i].y1);
						points_a[2]=Point(lines[j].x1,lines[i].y1);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}

				}
			}
		}
	}
	for (multimap<float, array<Point,3>>::iterator it = points.begin(); it!=points.end(); ++it)
	{
		float dist = (*it).first;
		pair<multimap<float,array<Point,3>>::iterator,multimap<float,array<Point,3>>::iterator> range = points.equal_range(dist);
		for (multimap<float, array<Point,3>>::iterator it2 = range.first; it2!=range.second ; ++it2)
		{
			if (isSquare2((*it).second,(*it2).second,p_offset))
			{
				Point A=(*it).second[1];
				Point B=(*it).second[0];
				Point C=(*it).second[2];
				Point D=(*it2).second[0];
				squares.push_back(Square(A,B,C,D));
			}
		}
	}
	return squares;
}

