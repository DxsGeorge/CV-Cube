#include "Hough_Transform.h"

vector<Vec4i> HoughTransform (Mat src, Mat &dst)
{
	//pyrDown(src,src,Size(src.cols/2,src.rows/2));
	//cvtColor(src,dst,CV_BGR2GRAY);
	GaussianBlur(dst,dst,Size(3,3),0,0);
	//adaptiveThreshold(src,src,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,11,2); 
	Canny(dst, dst, 50, 100, 3);
    vector<Vec4i> vec_lines;
    HoughLinesP(dst, vec_lines, 1, CV_PI/180, 80, 50, 10 );
	return vec_lines;
}