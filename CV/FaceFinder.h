#pragma once

#include "Line.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <map>
#include <math.h>
#include <array>

using namespace std;
using namespace cv;

vector<Point> FindIntersectionSpots (vector<Line> lines, int l_offset, float p_offset);

vector<Square> FindSquares(vector<Point> points, float offset);

vector<Square> FindSquares(vector <Line> lines,int p_offset, float l_offset);

vector<Square> FindSquares2(vector <Line> lines,int p_offset, float l_offset);

vector <Square> FindGridSquares(vector<Square> squares, float offset1);

vector<Line> gridLines(vector<Line> lines, float offset);

float roundf(float val);