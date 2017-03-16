#include "Hough_Transform.h"

vector<Vec4i> HoughTransform (Mat &src, Mat &dst,int canny_p[], int hough_p[])
{
	//pyrDown(src,src,Size(src.cols/2,src.rows/2));
	Mat src1(src);
	Mat dst1(src.cols/2,src.rows/2,CV_8UC1);
		
	pyrDown(src1,src1,Size(src.cols/2,src.rows/2));	
	cvtColor(src1,src1,CV_BGR2GRAY);
	//medianBlur(src1,src1,7);	
	GaussianBlur(src1,src1,Size(5,5),0,0);
	//bilateralFilter(src,src1,9,75,75);	
	Laplacian(src1,dst,CV_16SC1,3);
	compare(dst,8,dst,CV_CMP_GT);
	compare(src1,100, dst1, CV_CMP_LT);
	bitwise_and(dst,dst1,dst);
	convertScaleAbs(dst,dst,1,0);
	//Mat element=getStructuringElement(MORPH_RECT,Size(1,1));
	//erode(dst,dst,element);
	//dilate(dst,dst,element);
	//cvtColor(dst,dst,CV_BGR2GRAY);	
	//adaptiveThreshold(dst,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,2); 
	//threshold(dst,dst,0,255,CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	//Canny(dst, dst, canny_p[0], canny_p[1], canny_p[2]);
    vector<Vec4i> vec_lines;
    HoughLinesP(dst, vec_lines, 1, CV_PI/45, hough_p[0], hough_p[1], hough_p[2] );
	pyrUp(src1,src1,Size(dst.cols*2,dst.rows*2));
	//pyrUp(dst,dst,Size(src.cols,src.rows));
	src1.copyTo(src);
	return vec_lines;
}