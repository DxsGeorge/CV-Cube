#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "Line.h"
#include "FaceFinder.h"
#include "Hough_Transform.h"
#include "Input.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace cv;
using namespace std;



int main()
{
	//Define Algorith Margins

	int p_offset = 5; //limit of checking for same points
	float l_offset = 0.1; //limit of checking for vertical lines
	int s_offset=5; //limit of checking for same lines
	int canny_p[3]={50,200,3}; //Canny parameters	
	int hough_p[3]={50,100,50}; //HoughLinesP parameters
	int C_lowThreshold=50;
	int H_lowThreshold1=100;
	int H_lowThreshold2=100;
	int H_lowThreshold3=50;
	int const max_lowThreshold = 100;
	int const max_H_Threshold = 200;
	namedWindow("video",1);
	namedWindow("Canny",1);
	createTrackbar("Canny:", "Canny", &C_lowThreshold, max_lowThreshold);
	createTrackbar("Hough 1:", "Canny", &H_lowThreshold1, max_H_Threshold);
	createTrackbar("Hough 2:", "Canny", &H_lowThreshold2, max_H_Threshold);
	createTrackbar("Hough 3:", "Canny", &H_lowThreshold3, max_H_Threshold);
	//Video capture

	VideoCapture cap(1);
	Mat src_copy;
	while (true)
	{
		int canny_p[3]={C_lowThreshold,C_lowThreshold*3,3};
		int hough_p[3]={H_lowThreshold1,H_lowThreshold2,H_lowThreshold3};
		Mat src;
		cap >> src; 
		flip(src,src,1);

		//HoughTransform on captured frame

		if (!src.empty())
		{
			src.copyTo(src_copy);
			Mat dst;
			cvtColor(src,dst,CV_BGR2GRAY);
			vector<Vec4i> vec_lines;
			vec_lines=HoughTransform(src,dst,canny_p,hough_p);
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
			cvtColor(dst,dst,CV_GRAY2BGR);
			for (size_t i=0;i<lines.size();i++)
			{
				line( dst, Point(lines[i].x1, lines[i].y1), Point(lines[i].x2, lines[i].y2), Scalar(0,0,255), 1, CV_AA);
			}
			for (size_t i=0; i<SamePoints.size() ; i++)
			{
				std::ostringstream text;
				text<<"("<<SamePoints[i].x<<","<<SamePoints[i].y<<")";
				string text1 = text.str();
				circle (dst, SamePoints[i], 1, Scalar(0,255,0), 2);
				putText(dst,text1, SamePoints[i],FONT_HERSHEY_SIMPLEX,0.33,Scalar(0,255,0));
			}
			
			imshow("video",src);
			imshow("Canny",dst);
		}
		if( waitKey(1) == 27 ) break;
		Sleep(33);
	}
}