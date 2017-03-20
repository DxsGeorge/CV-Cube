#pragma once

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

void SurfDetectFeatures(Mat src, Mat &dst, Mat templ);

int FastDetectFeatures(Mat src, Mat &dst, int thresh);

void ORBDetectFeatures(Mat src, Mat &dst, Mat templ);

bool BlobDetectFeatures(Mat src, Mat &dst, vector<Point> &points);