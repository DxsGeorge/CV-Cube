#include "FeatureDetector.h"

void SurfDetectFeatures(Mat src, Mat &dst, Mat templ)
{
	int minHessian = 800;
	SurfFeatureDetector detector( minHessian );
	vector<KeyPoint> keypoints_object, keypoints_scene;
	detector.detect( templ, keypoints_object );
	detector.detect( src, keypoints_scene );
	SurfDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	extractor.compute( templ, keypoints_object, descriptors_object );
	extractor.compute( src, keypoints_scene, descriptors_scene );
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors_object, descriptors_scene, matches );
	double max_dist = 0; 
	double min_dist = 100;
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );
	vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		if( matches[i].distance < 2*min_dist ) good_matches.push_back( matches[i]); 
	}
	Mat img_matches;
	
	drawMatches( templ, keypoints_object, src, keypoints_scene,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), 2 );
			   
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;
	//vector<Point> points;
	for( int i = 0; i < good_matches.size(); i++ )
	{
		//-- Get the keypoints from the good matches
		obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
		scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
	}
	
	if (obj.size()>4)
	{
		Mat H = findHomography( obj, scene, CV_RANSAC );
		std::vector<Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0,0); 
		obj_corners[1] = cvPoint( templ.cols, 0 );
		obj_corners[2] = cvPoint( templ.cols, templ.rows ); 
		obj_corners[3] = cvPoint( 0, templ.rows );
		std::vector<Point2f> scene_corners(4);
		perspectiveTransform( obj_corners, scene_corners, H);
		
		line( img_matches, scene_corners[0] + Point2f( templ.cols, 0), scene_corners[1] + Point2f( templ.cols, 0), Scalar(0, 255, 0), 4 );
		line( img_matches, scene_corners[1] + Point2f( templ.cols, 0), scene_corners[2] + Point2f( templ.cols, 0), Scalar( 0, 255, 0), 4 );
		line( img_matches, scene_corners[2] + Point2f( templ.cols, 0), scene_corners[3] + Point2f( templ.cols, 0), Scalar( 0, 255, 0), 4 );
		line( img_matches, scene_corners[3] + Point2f( templ.cols, 0), scene_corners[0] + Point2f( templ.cols, 0), Scalar( 0, 255, 0), 4 );
		
		//cout<<r.size();
		imshow( "Good Matches & Object detection", img_matches );
	}
}

int FastDetectFeatures(Mat src, Mat &dst, int thresh)
{
	vector<KeyPoint> kp;
	FAST(src,kp,0,false);
	drawKeypoints(dst,kp,dst,Scalar(255,0,0));
	return kp.size();
}

void ORBDetectFeatures(Mat src, Mat &dst, Mat templ)
{
	int minHessian = 400;
	FastFeatureDetector detector(minHessian);
	vector<KeyPoint> keypoints_object, keypoints_scene;
	detector.detect( templ, keypoints_object );
	detector.detect( src, keypoints_scene );
	OrbDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	extractor.compute( templ, keypoints_object, descriptors_object );
	extractor.compute( src, keypoints_scene, descriptors_scene );
	descriptors_scene.convertTo(descriptors_scene, CV_32F);
    descriptors_object.convertTo(descriptors_object, CV_32F);
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors_object, descriptors_scene, matches );
	double max_dist = 0; double min_dist = 100;
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );
	vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		if( matches[i].distance < 3*min_dist ) good_matches.push_back( matches[i]); 
	}
	Mat img_matches;
	drawMatches( templ, keypoints_object, src, keypoints_scene,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;
	for( int i = 0; i < good_matches.size(); i++ )
	{
		//-- Get the keypoints from the good matches
		obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
		scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
	}
	if (obj.size()>4)
	{
		Mat H = findHomography( obj, scene, CV_RANSAC );
		std::vector<Point2f> obj_corners(4);
		obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( templ.cols, 0 );
		obj_corners[2] = cvPoint( templ.cols, templ.rows ); obj_corners[3] = cvPoint( 0, templ.rows );
		std::vector<Point2f> scene_corners(4);
		perspectiveTransform( obj_corners, scene_corners, H);
		line( dst, scene_corners[0] + Point2f( templ.cols, 0), scene_corners[1] + Point2f( templ.cols, 0), Scalar(0, 255, 0), 4 );
		line( dst, scene_corners[1] + Point2f( templ.cols, 0), scene_corners[2] + Point2f( templ.cols, 0), Scalar( 0, 255, 0), 4 );
		line( dst, scene_corners[2] + Point2f( templ.cols, 0), scene_corners[3] + Point2f( templ.cols, 0), Scalar( 0, 255, 0), 4 );
		line( dst, scene_corners[3] + Point2f( templ.cols, 0), scene_corners[0] + Point2f( templ.cols, 0), Scalar( 0, 255, 0), 4 );
		imshow( "Good Matches & Object detection", img_matches );
	}
}