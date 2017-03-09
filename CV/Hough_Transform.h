#pragma once

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

vector<Vec4i> HoughTransform (Mat &src, Mat &dst,int canny_p[], int hough_p[]);