#include "FaceFinder.h"
#include "MyHash.h"

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
			Point a;
			if (max(lines[i].length(),lines[j].length())/min(lines[i].length(),lines[j].length())<1.3)
			{
				if (PerpLines(lines[i],lines[j],l_offset))
				{					
					if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x1,lines[j].y1),p_offset)) 
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x1,lines[i].y1);
						points_a[1]=Point(lines[i].x2,lines[i].y2);
						points_a[2]=Point(lines[j].x2,lines[j].y2);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if	(SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x2,lines[j].y2),p_offset)) 
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x1,lines[i].y1);
						points_a[1]=Point(lines[i].x2,lines[i].y2);
						points_a[2]=Point(lines[j].x1,lines[j].y1);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if	(SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),p_offset))
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x2,lines[i].y2);
						points_a[1]=Point(lines[i].x1,lines[i].y1);
						points_a[2]=Point(lines[j].x2,lines[j].y2);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if	(SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x2,lines[j].y2),p_offset)) 
					{
						array<Point,3> points_a;
						points_a[0]=Point(lines[i].x2,lines[i].y2);
						points_a[1]=Point(lines[i].x1,lines[i].y1);
						points_a[2]=Point(lines[j].x1,lines[j].y1);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}					
				}
			}
			if (intersection3(lines[i].getPoint(1),lines[i].getPoint(2),lines[j].getPoint(1),lines[j].getPoint(2),a))
			{
				if (PerpLines(lines[i],lines[j],l_offset))
				{					
					if (max(Distance(lines[i].getPoint(1),a),Distance(lines[j].getPoint(1),a))/min(Distance(lines[i].getPoint(1),a),Distance(lines[j].getPoint(1),a))<1.3)
					{
						array<Point,3> points_a;
						points_a[0]=a;
						points_a[1]=lines[i].getPoint(1);
						points_a[2]=lines[j].getPoint(1);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if (max(Distance(lines[i].getPoint(1),a),Distance(lines[j].getPoint(2),a))/min(Distance(lines[i].getPoint(1),a),Distance(lines[j].getPoint(2),a))<1.3)
					{
						array<Point,3> points_a;
						points_a[0]=a;
						points_a[1]=lines[i].getPoint(1);
						points_a[2]=lines[j].getPoint(2);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if (max(Distance(lines[i].getPoint(2),a),Distance(lines[j].getPoint(1),a))/min(Distance(lines[i].getPoint(2),a),Distance(lines[j].getPoint(1),a))<1.3)
					{
						array<Point,3> points_a;
						points_a[0]=a;
						points_a[1]=lines[i].getPoint(2);
						points_a[2]=lines[j].getPoint(1);
						float dist=Distance(points_a[1],points_a[2]);
						points.insert(pair<float,array<Point,3> >(dist,points_a));
					}
					else if (max(Distance(lines[i].getPoint(2),a),Distance(lines[j].getPoint(2),a))/min(Distance(lines[i].getPoint(2),a),Distance(lines[j].getPoint(2),a))<1.3)
					{
						array<Point,3> points_a;
						points_a[0]=a;
						points_a[1]=lines[i].getPoint(2);
						points_a[2]=lines[j].getPoint(2);
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
		multimap<float, array<Point,3>>::iterator itlow=points.lower_bound(dist-10);
		multimap<float, array<Point,3>>::iterator ithi=points.upper_bound(dist+10);		
		//pair<multimap<float,array<Point,3>>::iterator,multimap<float,array<Point,3>>::iterator> range = points.equal_range(dist);
		//for (multimap<float, array<Point,3>>::iterator it2 = range.first; it2!=range.second ; ++it2)
		for (multimap<float, array<Point,3>>::iterator it2 = itlow; it2!=ithi ; ++it2)
		{
			Point points1[3];
			Point points2[3];
			copy(begin((*it).second),end((*it).second),begin(points1));
			copy(begin((*it2).second),end((*it2).second),begin(points2));
			if (isSquare2(points1,points2,dist,Distance((*it).second[0],(*it2).second[0]),p_offset))
			{
				Point A=(*it).second[1];
				Point B=(*it).second[0];
				Point C=(*it).second[2];
				Point D=(*it2).second[0];
				Square *square1 = new Square(A,B,C,D);
				int area=square1->Area();
				if (area>50) squares.push_back(*square1);
			}
			
		}
	}
	return squares;
}

vector<Square> FindSquares2(vector <Line> lines,int p_offset, float l_offset)
{
	vector<Square> squares;
	HashTable table;
	for (size_t i=0;i<lines.size();++i)
	{
		for (size_t j=i+1;j<lines.size();++j)
		{
			if (abs(lines[i].length()-lines[j].length())<1000)
			{
				//if (PerpLines(lines[i],lines[j],l_offset))
				//{
					if (SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x1,lines[j].y1),p_offset)) 
					{
						Item *a=new Item();						
						a->same=Point(lines[i].x1,lines[i].y1);
						a->point1=Point(lines[i].x2,lines[i].y2);
						a->point2=Point(lines[j].x2,lines[i].y2);
						a->key=Distance(a->point1,a->point2);
						table.insertItem(a);
					}
					else if	(SamePoint(Point(lines[i].x1,lines[i].y1),Point(lines[j].x2,lines[j].y2),p_offset)) 
					{
						Item *a=new Item();					
						a->same=Point(lines[i].x1,lines[i].y1);
						a->point1=Point(lines[i].x2,lines[i].y2);
						a->point2=Point(lines[j].x1,lines[i].y1);
						a->key=Distance(a->point1,a->point2);
						table.insertItem(a);
					}
					else if	(SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x1,lines[j].y1),p_offset))
					{
						Item *a=new Item();					
						a->same=Point(lines[i].x2,lines[i].y2);
						a->point1=Point(lines[i].x1,lines[i].y1);
						a->point2=Point(lines[j].x2,lines[i].y2);
						a->key=Distance(a->point1,a->point2);
						table.insertItem(a);
					}
					else if	(SamePoint(Point(lines[i].x2,lines[i].y2),Point(lines[j].x2,lines[j].y2),p_offset)) 
					{
						Item *a=new Item();					
						a->same=Point(lines[i].x2,lines[i].y2);
						a->point1=Point(lines[i].x1,lines[i].y1);
						a->point2=Point(lines[j].x1,lines[i].y1);
						a->key=Distance(a->point1,a->point2);
						table.insertItem(a);
					}

				//}
			}
		}
	}
	for (int i=0; i<table.getLength(); ++i)
	{
		if (table.list[i].getLength()<2) break;
		else 
		{
			vector<Item> items=table.list[i].getAllItems();
			for (size_t j=0; j<items.size(); ++j)
			{
				for (size_t k=j+1;k<items.size();++k)
				{
					Point points1[3]={items[j].same,items[j].point1,items[j].point2};
					Point points2[3]={items[k].same,items[k].point1,items[k].point2};
					if (isSquare2(points1,points2,Distance(points1[1],points1[2]),Distance(points2[1],points2[2]),l_offset)) 
					{
						Point A=items[j].point1;
						Point B=items[j].same;
						Point C=items[j].point2;
						Point D=items[k].same;
						squares.push_back(Square(A,B,C,D));
					}

				}
			}
		}
	}
	return squares;
}

vector <Square> FindGridSquares(vector<Square> squares, float offset1)
{
	vector<Square> gridsquares;
	for (size_t i=0;i<squares.size();++i)
	{ 
		int detects=0;
		vector<Square> tempsquares;
		for (size_t j=i+1;j<squares.size();++j)
		{
			tempsquares.clear();
			if ((VerticalLines(Line(squares[i].getPoint(1),squares[i].getPoint(2)),Line(squares[j].getPoint(1),squares[j].getPoint(2)),offset1) ||
				VerticalLines(Line(squares[i].getPoint(2),squares[i].getPoint(3)),Line(squares[j].getPoint(1),squares[j].getPoint(2)),offset1)) &&
				abs(squares[i].Area()-squares[j].Area())<1000 && 
				absDifference(squares[i].getCenter(),squares[j].getCenter())>=squares[i].sideSize() &&
				abs(squares[i].sideSize()-squares[j].sideSize())<20)
			{
				detects++;
				tempsquares.push_back(squares[j]);
			}
			tempsquares.push_back(squares[i]);
			if (detects>6) 
			{
				for (size_t j=0; j<tempsquares.size(); ++j)
				{
					gridsquares.push_back(tempsquares[j]);						
				}
			}
		}
	}
	if (gridsquares.size()>5) cout<<"Success! \n";
	return gridsquares;
}

vector<Line> gridLines(vector<Line> lines, float offset)
{
	vector<Line> gridlines;
	int detects1,detects2;
	for (size_t i=0; i<lines.size();++i)
	{
		detects1=detects2=0;
		for (size_t j=i+1;j<lines.size();++j)
		{
			if (
				CheckParallel(lines[i],lines[j]) && 
				max(lines[i].length(),lines[j].length())/min(lines[i].length(),lines[j].length())<1.2 
				//max(lines[i].length(),Distance(lines[i],lines[j]))/min(lines[i].length(),Distance(lines[i],lines[j]))<1.2
				)
			{
				detects1++;
			}
		}
		if (detects1>2) 
		{
			for (size_t j=i+1;j<lines.size();++j)
			{
				if (
					VerticalLines(lines[i],lines[j],offset) && 
					max(lines[i].length(),lines[j].length())/min(lines[i].length(),lines[j].length())<1.2 &&
					intersection3(lines[i].getPoint(1),lines[i].getPoint(2),lines[j].getPoint(1),lines[j].getPoint(2))
					) 
				{
					detects2++;
				}
			}
		}
		if (detects2>2) gridlines.push_back(lines[i]);
	}
	if (gridlines.size()>=4) cout<<"Success! \n\a";
	return gridlines;

}

void ShowFace(Mat src, vector<Point> points)
{
	int maxval[3]={0,0,0};
	for (int i=points[0].x;i<points[1].x;i++)
	{
		for (int j=points[0].y;j<points[1].y;j++)
		{
			Vec3b intensity=src.at<Vec3b>(j,i);
			if (maxval[0]<intensity[0]) maxval[0]=intensity[0];
			if (maxval[1]<intensity[1]) maxval[1]=intensity[1];
			if (maxval[2]<intensity[2]) maxval[2]=intensity[2];
		}
	}
	Vec3b topleft=src.at<Vec3b>(points[0]);
	Vec3b midtop=src.at<Vec3b>(Point((points[0].x+points[1].x)/2,points[0].y));
	Vec3b topright=src.at<Vec3b>(Point(points[1].x,points[0].y));
	Vec3b midleft=src.at<Vec3b>(Point(points[0].x,(points[1].y+points[1].y)/2));
	Vec3b mid=src.at<Vec3b>(Point((points[0].x+points[1].x)/2,(points[0].y+points[1].y)/2));
	Vec3b midright=src.at<Vec3b>(Point(points[1].x,(points[0].y+points[1].y)/2));
	Vec3b leftbot=src.at<Vec3b>(Point(points[0].x,points[1].y));
	Vec3b midbot=src.at<Vec3b>(Point((points[0].x+points[1].x)/2,points[1].y));
	Vec3b rightbot=src.at<Vec3b>(points[1]);
	cout<<ColorMatcher(topleft,maxval)<<"|"<<ColorMatcher(midtop,maxval)<<"|"<<ColorMatcher(topright,maxval)<<"\n";
	cout<<ColorMatcher(midleft,maxval)<<"|"<<ColorMatcher(mid,maxval)<<"|"<<ColorMatcher(midright,maxval)<<"\n";
	cout<<ColorMatcher(leftbot,maxval)<<"|"<<ColorMatcher(midbot,maxval)<<"|"<<ColorMatcher(rightbot,maxval)<<"\n";
	cout<<maxval[0]<<","<<maxval[1]<<","<<maxval[2]<<"\n";
	circle(src,points[0],3, Scalar(topleft.val[0],topleft.val[1],topleft.val[2]), -1, 8);
	//circle(src,Point((points[0].x+points[1].x)/2,points[0].y),3, Scalar(0,255,0), -1, 8);
	circle(src,Point((points[0].x+points[1].x)/2,points[0].y),3, Scalar(0,255,0), -1, 8);
}

float middle(float x , float y, float z)
	{
		if(x<=y && y<= z)
			return y;
		if(y<=x && x<=z)
			return x;
		if(x<=z && z<=y)
			return z;
	}

string ColorMatcher(Vec3b values, int maxval[])
{
	//B = 0 | G = 1 | R = 2
	//BGR values below
	//RED(0,0,255) 0, GREEN (68,154,0) 0.44, BLUE(155,61,0) 0.39, ORANGE(0,80,254) 0.31, YELLOW (0,215,255) 0.84, WHITE (255,255,255) 1
	float max1=max(values[0],max(values[1],values[2]));
	float div=middle(values[0],values[1],values[2])/max1;
	if (div<0.3) return "red";
	else if (div<0.39) return "orange";
	else if (div<0.45) return "blue";
	else if (div<0.85) return "green";
	else if (div<1) return "yellow";
	else return "white";
}


