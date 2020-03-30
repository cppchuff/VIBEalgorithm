#include <iostream>
#include <string.h>
#include <stdio.h>
#include "BackgroundSubtract.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	

	//vector<Vec4i> g_vHierarchy;

	cv::VideoCapture cap("EZVZ0048.MP4");
	if (cap.isOpened() == NULL)
	{
		cout << "empity" << endl;
		return -1;
	}

	cv::Mat image, imageGray;
	cv::Mat foregroundGray;
	BackgroundSubtract subtractor;

	cap >> image;
	cv::cvtColor(image, imageGray, COLOR_BGR2GRAY);
	imageGray.copyTo(foregroundGray);
	subtractor.init(imageGray);

	while (!image.empty())
	{

		//vector<vector<cv::Point>> g_vContours;

		subtractor.subtract(imageGray, foregroundGray);

		GaussianBlur(foregroundGray, foregroundGray, Size(7, 7), 0);

		//findContours(foregroundGray, g_vContours, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		//std::cout << endl << endl << g_vContours[0] << endl << endl;

		namedWindow("foreground",WINDOW_NORMAL);
		imshow("foreground", foregroundGray);
		cap >> image;
		cv::cvtColor(image, imageGray, COLOR_BGR2GRAY);

		int c = cv::waitKey(20);
		if (c == 27)
		{
			break;
		}
	}

	return 0;
}
