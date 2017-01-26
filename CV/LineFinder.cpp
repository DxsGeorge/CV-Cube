#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

using namespace cv;

bool Near_Points (int x1, int x2, int y1, int y2)
{
	if (abs(x1-x2)<10 && abs(y1-y2) < 10) return true;
	else return false;
}

bool Perp_Lines (int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4)
{
	int dx1=x1-x2;
	int dx2=x3-x4;
	int dy1=y1-y2;
	int dy2=y3-y4;
	double sl1=dy1/dx1;
	double sl2=dy2/dx2;
	if (abs(sl1+1/sl2) < 0.5) return true;
	else return false;
}

int main(int argc, char** argv)
{
	RNG rng(12345);
    Mat dst, color_dst;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat src=imread("C:\\Users\\user\\Desktop\\CV\\webcam-toy-photo1.jpg",-1);
	GaussianBlur(src, src, Size(3,3), 0, 0);
	Laplacian(src,src,CV_8U,3,1,0);
	//pyrDown(src, src, Size( src.cols/2, src.rows/2) );
	cvtColor(src,src,CV_BGR2GRAY);
	threshold(src,src,12,255,THRESH_BINARY);
	//adaptiveThreshold(src,src,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,11,2);
	Canny( src, dst, 50, 200, 3 );
    cvtColor( dst, color_dst, CV_GRAY2BGR );
	
#if 0
	findContours(dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros( dst.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
    {
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
#elif 1
	//Hough

    vector<Vec4i> lines;
	vector <Point> intersec_points;
    HoughLinesP( dst, lines, 1, CV_PI/180, 50, 50, 10 );
	
	for (size_t i = 0; i<lines.size(); i++)
	{
		for (size_t j = i+1; j<lines.size(); j++)
		{
			if (Near_Points(lines[i][0], lines[j][0],lines[i][1], lines[j][1]) || 
				Near_Points(lines[i][0], lines[j][2],lines[i][1], lines[j][3])) 
			{
				if (Perp_Lines(lines[i][0],lines[i][2],lines[j][0],lines[j][2],lines[i][1],lines[i][3],lines[j][1],lines[j][3]))
				intersec_points.push_back(Point(lines[i][0],lines[i][1]));
			}

		}
	}
	
    for(size_t i = 0; i < lines.size(); i++ )
    {
        line( color_dst, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 1, 8 );
    }
	for (size_t i=0; i<intersec_points.size();i++)
	{
		circle (color_dst, Point(intersec_points[i]),1,Scalar(0,255,0),3);
	}
    namedWindow( "Source", 1 );
    imshow( "Source", src );
	//pyrUp(src, src, Size( src.cols*2, src.rows*2) );
#endif
	//pyrUp(color_dst, color_dst, Size( src.cols*2, src.rows*2) );
    namedWindow( "Detected Lines", 1 );
    imshow( "Detected Lines", color_dst );
    waitKey(0);
    return 0;
}

