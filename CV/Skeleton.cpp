#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

using namespace cv;

int main(int argc, char** argv)
{
    Mat dst, color_dst;
	Mat src=imread("C:\\Users\\user\\Desktop\\CV\\index.jpg",0);
	threshold(src, src, 127, 255, THRESH_BINARY); 
	Mat skel(src.size(), CV_8UC1, Scalar(0));
	Mat temp;
	Mat eroded;
 
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
 
	bool done;		
	do
	{
	  erode(src, eroded, element);
	  dilate(eroded, temp, element); // temp = open(src)
	  subtract(src, temp, temp);
	  //skel= skel | temp;
	  bitwise_or(skel, temp, skel);
	  eroded.copyTo(src);
 
	  done = (countNonZero(src) == 0);
	} while (!done);
	imshow("Image", src);
    waitKey(0);
}