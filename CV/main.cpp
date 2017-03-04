#include <opencv2/highgui/highgui.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/photo/photo.hpp"
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
	//cout << "OpenCV version : " << CV_VERSION << endl; //shows version, currently 2.4.10
	bool track_intersections = false;
	//Define Algorithm Margins
	
	int p_offset = 5; //limit of checking for same points
	float l_offset = 0.1; //limit of checking for vertical lines
	int s_offset=5; //limit of checking for same lines
	int canny_p[3]={50,200,5}; //Canny parameters	
	int hough_p[3]={50,100,50}; //HoughLinesP parameters

	//Test Hough and Canny Parameters

	int mode=1;
	bool video=false;
	int C_lowThreshold=50;
	int H_lowThreshold1=100;
	int H_lowThreshold2=100;
	int H_lowThreshold3=5;
	int const max_lowThreshold = 200;
	int const max_H_Threshold = 200;
	namedWindow("video",1);
	namedWindow("Canny",1);
	createTrackbar("Canny:", "Canny", &C_lowThreshold, max_lowThreshold);
	createTrackbar("Hough 1:", "Canny", &H_lowThreshold1, max_H_Threshold);
	createTrackbar("Hough 2:", "Canny", &H_lowThreshold2, max_H_Threshold);
	createTrackbar("Hough 3:", "Canny", &H_lowThreshold3, max_H_Threshold);
	bool init=true; // initialize LK

	//cin >> mode;

	//Video capture
	if (video) 
	{
		VideoCapture cap(1);
		Mat src_copy;
		while (true)
		{
			int canny_p[3]={C_lowThreshold,C_lowThreshold*3,3};
			int hough_p[3]={H_lowThreshold1,H_lowThreshold2,H_lowThreshold3};
			Mat src;
			cap >> src; 
			cap.set(CV_CAP_PROP_BRIGHTNESS,40);
			cap.set(CV_CAP_PROP_CONTRAST,20);
			flip(src,src,1);

			switch (mode)
			{
				case 1:

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
					cout << lines.size() << "\n";

					//Find Intersections
				

					vector <Point> SamePoints;
					SamePoints=FindIntersectionSpots(lines,p_offset,l_offset);
					vector<Square> squares;
					//squares=FindSquares(lines, p_offset, l_offset);
					squares=FindSquares(SamePoints,  l_offset);
					//Draw

					cvtColor(dst,dst,CV_GRAY2BGR);
	#if (!track_intersections)
					for (size_t i=0;i<lines.size();i++)
					{
						line( dst, Point(lines[i].x1, lines[i].y1), Point(lines[i].x2, lines[i].y2), Scalar(0,0,255), 1, CV_AA);
					}
					for (size_t i=0;i<squares.size();i++)
					{
						line( dst, squares[i].getPoint(1), squares[i].getPoint(2), Scalar(0,255,0), 1, CV_AA);
						line( dst, squares[i].getPoint(2), squares[i].getPoint(3), Scalar(0,255,0), 1, CV_AA);
						line( dst, squares[i].getPoint(3), squares[i].getPoint(4), Scalar(0,255,0), 1, CV_AA);
						line( dst, squares[i].getPoint(4), squares[i].getPoint(1), Scalar(0,255,0), 1, CV_AA);
					}
				
	#elif (track_intersections)
				for (size_t i=0; i<SamePoints.size() ; i++)
				{
					//std::ostringstream text;
					//text<<"("<<SamePoints[i].x<<","<<SamePoints[i].y<<")";
					//string text1 = text.str();
					circle (dst, SamePoints[i], 1, Scalar(0,255,0), 2);
					
					
					
					//putText(dst,text1, SamePoints[i],FONT_HERSHEY_SIMPLEX,0.33,Scalar(0,255,0));
				}
				/*
				for (size_t i=0; i<squares.size() ; i++)
				{
					circle (dst, squares[i].getPoint(1), 1, Scalar(255,0,0), 2);
					circle (dst, squares[i].getPoint(2), 1, Scalar(255,0,0), 2);
					circle (dst, squares[i].getPoint(3), 1, Scalar(255,0,0), 2);
					circle (dst, squares[i].getPoint(4), 1, Scalar(255,0,0), 2);
					vector<Point> sqpoints;
					sqpoints.push_back(squares[i].getPoint(1));
					sqpoints.push_back(squares[i].getPoint(2));
					sqpoints.push_back(squares[i].getPoint(3));
					sqpoints.push_back(squares[i].getPoint(4));
					fillConvexPoly(dst, &sqpoints[0], 4, Scalar(255,0,0));
				}
				*/
	#endif			
					imshow("video",src);
					imshow("Canny",dst);
				}
				break;

				case 2:

					//OpticalFLow
	#pragma region
				if (!src.empty()) 
				{
					TermCriteria termcrit(TermCriteria::COUNT|TermCriteria::EPS,10,0.03);
					Size subPixWinSize(10,10), winSize(31,31);
					const int MAX_COUNT = 500;
					bool init = true;
					Mat gray, prevGray, image, frame;
					vector<Point2f> points[2];
					src.copyTo(image);
					cvtColor(image, gray, COLOR_BGR2GRAY);
					if( init )
					{
						// automatic initialization
						goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
						init=false;
					}
					else if( !points[0].empty() )
					{
						vector<uchar> status;
						vector<float> err;
						if(prevGray.empty()) gray.copyTo(prevGray);
						calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);
						size_t i, k;
						for( i = k = 0; i < points[1].size(); i++ )
						{
							if( !status[i] )
								continue;

							points[1][k++] = points[1][i];
							circle( image, points[1][i], 3, Scalar(0,255,0), -1, 8);
						}
						points[1].resize(k);
					}
					imshow("LK Demo", image);
					std::swap(points[1], points[0]);
					cv::swap(prevGray, gray);
					break;
	#pragma endregion
					}
			}

		if( waitKey(1) == 27 ) break;
		//Sleep(33);
		}
	}
	else 
	{
		while(true)
		{
			Mat test=imread("C:/Users/user/Desktop/CV/test.jpg",1);
			int canny_p[3]={C_lowThreshold,C_lowThreshold*3,3};
			int hough_p[3]={H_lowThreshold1,H_lowThreshold2,H_lowThreshold3};
			Mat dst;
			cvtColor(test,dst,CV_BGR2GRAY);
			vector<Vec4i> vec_lines;
			vec_lines=HoughTransform(test,dst,canny_p,hough_p);
			vector <Line> lines;
			lines.reserve(vec_lines.size());	
			for (size_t i=0;i<vec_lines.size(); i++)
			{
				lines.push_back(Line(vec_lines[i][0],vec_lines[i][1],vec_lines[i][2],vec_lines[i][3]));
			}
			cout << lines.size() << "\n";

			//vector <Point> SamePoints;
			//SamePoints=FindIntersectionSpots(lines,p_offset,l_offset);
			vector<Square> squares;
			squares=FindSquares(lines, p_offset, l_offset);
			//squares=FindSquares(SamePoints,  l_offset);

			for (size_t i=0;i<lines.size();i++)
			{
				line( test, Point(lines[i].x1, lines[i].y1), Point(lines[i].x2, lines[i].y2), Scalar(0,0,255), 1, CV_AA);
				//circle (test, Point(lines[i].x1, lines[i].y1), 1, Scalar(255,255,0), 2);
				//circle (test, Point(lines[i].x2, lines[i].y2), 1, Scalar(255,255,0), 2);
			}
			/*
			for (size_t i=0; i<SamePoints.size() ; i++)
			{
				//std::ostringstream text;
				//text<<"("<<SamePoints[i].x<<","<<SamePoints[i].y<<")";
				//string text1 = text.str();
				circle (test, SamePoints[i], 1, Scalar(0,255,0), 2);
					
					
					
				//putText(dst,text1, SamePoints[i],FONT_HERSHEY_SIMPLEX,0.33,Scalar(0,255,0));
			}
			*/
			for (size_t i=0; i<squares.size() ; i++)
			{
				circle (test, squares[i].getPoint(1), 1, Scalar(255,255,0), 2);
				circle (test, squares[i].getPoint(2), 1, Scalar(255,255,0), 2);
				circle (test, squares[i].getPoint(3), 1, Scalar(255,255,0), 2);
				circle (test, squares[i].getPoint(4), 1, Scalar(255,255,0), 2);
			}
			imshow("video",dst);
			imshow("Canny",test);
			if( waitKey(1) == 27 ) break;
		}
	}
	 
}