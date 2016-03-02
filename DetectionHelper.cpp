#include "stdafx.hpp"
#include "magic.hpp"

using namespace std;
using namespace cv;

const Scalar U_LOW = Scalar(50, 0, 109);
const Scalar U_HIGH = Scalar(100, 255, 255);

static Mat createUMask(Mat& frame) {
	Mat hsvFrame;
	cvtColor(frame, hsvFrame, CV_BGR2HSV);

	Mat mask;
	inRange(hsvFrame, U_LOW, U_HIGH, mask);
		
	return mask;
}

static void cleanUMask(Mat& mask) {
	erode(mask, mask, Mat());
	erode(mask, mask, Mat());
	dilate(mask, mask, Mat());
	dilate(mask, mask, Mat());
}

static vector<vector<Point> > processContours(Mat& original, vector<Vec4i> hierarchy) {
	vector<vector<Point> > contours;

	findContours(original, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	return contours;
}
