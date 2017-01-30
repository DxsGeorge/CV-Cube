#include "Hough_Transform.h"

vector<Vec4i> HoughTransform (Mat src, Mat &dst,int canny_p[], int hough_p[])
{
	//pyrDown(src,src,Size(src.cols/2,src.rows/2));
	GaussianBlur(src,src,Size(3,3),0,0);	
	cvtColor(src,dst,CV_BGR2GRAY);	
	Laplacian(src,dst,CV_16SC1,3,1,0);
	convertScaleAbs(dst,dst,1,0);
	//cvtColor(dst,dst,CV_BGR2GRAY);	
	//adaptiveThreshold(src,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,11,2); 
	//threshold(dst,dst,0,255,CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	Canny(dst, dst, canny_p[0], canny_p[1], canny_p[2]);
    vector<Vec4i> vec_lines;
    HoughLinesP(dst, vec_lines, 1, CV_PI/180, hough_p[0], hough_p[1], hough_p[2] );
	return vec_lines;
}