#include "Hough_Transform.h"

vector<Vec4i> HoughTransform (Mat src)
{
	//pyrDown(src,src,Size(src.cols/2,src.rows/2));
	Mat dst,cdst;
	GaussianBlur(src,src,Size(3,3),0,0);
	//adaptiveThreshold(src,src,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,11,2); 
	Canny(src, dst, 66, 133, 3, true);
	cvtColor(dst, cdst, CV_GRAY2BGR);
    vector<Vec4i> vec_lines;
    HoughLinesP(dst, vec_lines, 1, CV_PI/180, 50, 50, 10 );
	return vec_lines;
}