#include "stdafx.hpp"
#include "DetectionHelper.cpp"
#include "NetworkTableHelper.cpp"
#include "DistanceHelper.cpp"
#include "magic.hpp"

using namespace std;
using namespace cv;

void processFrame(Mat& frame) {
	imshow("Input", frame);

	Mat mask = createUMask(frame);
	imshow("Dirty mask", mask);
	cleanUMask(mask);
	imshow("Clean mask", mask);

	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours = processContours(mask, hierarchy);

        for (int i = 0; i < contours.size(); i++) {
                vector<Point> approximatedLines;
                approxPolyDP(contours[i], approximatedLines, arcLength(contours[i], true) * 0.02, true);

 		RotatedRect boundingBox = minAreaRect(approximatedLines);
		Size2f size = boundingBox.size;
		double area = boundingBox.boundingRect().area();
		double uWidth = boundingBox.size.width;

		if (boundingBox.size.height > uWidth) {
			uWidth = boundingBox.size.height;
		}		
	
		if (area < 1500) {
			continue;
		}

		double distance = approxUDistance(uWidth);
		Point2f boundingBoxPoints[4];
		boundingBox.points(boundingBoxPoints);

		stringstream distanceStr;
		distanceStr << "Distance: " << distance;

		stringstream areaStr;
		areaStr << "Area: " << area;

		putText(frame, distanceStr.str(), Point(boundingBoxPoints[1].x, boundingBoxPoints[1].y - 20), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
		putText(frame, areaStr.str(), Point(boundingBoxPoints[1].x, boundingBoxPoints[1].y - 40), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
		circle(frame, boundingBox.center, 5, Scalar(255, 0, 0), 3);
                for (int pointIdx = 0; pointIdx < 4; pointIdx++) {
               		line(frame, boundingBoxPoints[pointIdx], boundingBoxPoints[(pointIdx + 1) % 4], Scalar(0, 255, 255), 3);
                }
        }
	
	imshow("Output", frame);
}

int main() {
	testNTs();
	VideoCapture webCam("http://192.168.1.100/mjpg/video.mjpg");
        waitKey(100); // Webcams don't 'open' immediately, so we give them a bit.
    	while (true) {
                Mat frame;
                webCam >> frame;

		resize(frame, frame, Size(frame.cols * 2, frame.rows * 2));		
                processFrame(frame);
                waitKey(10);
       	}

	return 0;
}
