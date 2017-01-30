#include "Hough_Transform.h"

vector<Vec4i> HoughTransform (Mat src, Mat &dst,int canny_p[], int hough_p[])
{
	//pyrDown(src,src,Size(src.cols/2,src.rows/2));
	cvtColor(src,dst,CV_BGR2GRAY);
	GaussianBlur(dst,dst,Size(3,3),0,0);
	//adaptiveThreshold(src,src,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,11,2); 
	Canny(dst, dst, canny_p[0], canny_p[1], canny_p[2]);
    vector<Vec4i> vec_lines;
    HoughLinesP(dst, vec_lines, 1, CV_PI/180, hough_p[0], hough_p[1], hough_p[2] );
	return vec_lines;
}