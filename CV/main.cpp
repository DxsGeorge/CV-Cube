#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "Line.h"
#include "FaceFinder.h"
#include "Hough_Transform.h"
#include "Input.h"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;



int main()
{
	int p_offset = 5; //offset for checking for same points
	float l_offset = 0.1; //offset for checking for vertical lines
	int s_offset=5; //offset for checking for same lines
	
	//Read Image

	string name="C:\\Users\\user\\Desktop\\CV\\webcam-toy-photo1.jpg";
    Mat src=ReadImage(name);
	Mat src_copy;
	src.copyTo(src_copy);
	Mat dst;
	cvtColor(src,dst,CV_BGR2GRAY);

	//Hough 

	vector<Vec4i> vec_lines;
	vec_lines=HoughTransform(src,dst);
	vector <Line> lines;
	lines.reserve(vec_lines.size());	
	for (size_t i=0;i<vec_lines.size(); i++)
	{
		lines.push_back(Line(vec_lines[i][0],vec_lines[i][1],vec_lines[i][2],vec_lines[i][3]));
	}

	//Find Intersections

	vector <Point> SamePoints;
	SamePoints=FindIntersectionSpots(lines,p_offset,l_offset);

	//Draw
	
	for (size_t i=0;i<lines.size();i++)
	{
		line( src, Point(lines[i].x1, lines[i].y1), Point(lines[i].x2, lines[i].y2), Scalar(0,0,255), 1, CV_AA);
    }
	for (size_t i=0; i<SamePoints.size() ; i++)
	{
		std::ostringstream text;
		text<<"("<<SamePoints[i].x<<","<<SamePoints[i].y<<")";
		string text1 = text.str();
		circle (src, SamePoints[i], 1, Scalar(0,255,0), 2);
		putText(src,text1, SamePoints[i],FONT_HERSHEY_SIMPLEX,0.33,Scalar(0,255,0));
	}
	imshow("Hough", src);
	imshow("Canny", dst);
	imshow("source",src_copy);
	imwrite("C:\\Users\\user\\Desktop\\CV\\2.jpg",src);

    waitKey(0);
}