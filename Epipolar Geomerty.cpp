#pragma once
#include "opencv2/highgui/highgui.hpp" //highgui module, as this contains the functions for input and output operations
#include "opencv2/core/core.hpp"
#include <iostream>
#include <stdlib.h>
#include <opencv2\imgproc.hpp>
using namespace cv;
using namespace std;
Mat Limage;
Mat Rimage;
Mat rows;
Mat cols;
Mat F;
Mat X; //for the point which is selected
Mat L; // a b c varuiables of line
void FundmentalMatrix()
{
	int fx = 877.24128;
	int fy = 876.55123;
	int cx = 543.98552;
	int cy = 368.43676;
	int fxR = 878.47023;
	int fyR = 877.80629;
	int cxR = 541.75639;
	int cyR = 393.95156;

	Mat K = (Mat_<double>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
	Mat R = (Mat_<double>(3, 3) << 0.7646, 0.0616, -0.6416, -0.0726, 0.9973, 0.0092, 0.6404, 0.0396, 0.7670);
	Mat T = (Mat_<double>(3, 1) << 294.92002, 7.71859, 102.50458);
	Mat Kp_inv = K.inv(); //for K inverse
	Mat a = (K * (R.t()) * T);
	int a1 = a.ptr<double>(0)[0];
	int a2 = a.ptr<double>(1)[0];
	int a3 = a.ptr<double>(2)[0];
	Mat c = (Mat_<double>(3, 3) << 0, -a3, a2, a3, 0, -a1, -a2, a1, 0); //Skew matrix of (matrix a )
	Mat Kp = (Mat_<double>(3, 3) << fxR, 0, cxR, 0, fyR, cyR, 0, 0, 1); // Intrinsic matrix of RIGHT Image
	F = (((Kp)* Kp_inv).t()) * (R * (K.t())) * (c); //Fundamental Matrix
	cout << F;
}

void onClickMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		circle(Limage, Point(x, y), 1, (255, 0, 0), 3); // Draws circle at the slected point
		X = (Mat_<double>(3, 1) << x, y, 1);
	}
}
int main()
{
	int argc;
	char** argv;
	//showimage();
	Limage = imread("C:/Users/19378/Desktop/Left_0.bmp");
	Rimage = imread("C:/Users/19378/Desktop/Right_0.bmp");
	while (1)
	{
		imshow("Right Image", Rimage);
		imshow("Left Image", Limage);
		setMouseCallback("Left Image", onClickMouse, NULL); //onClick
		creating a line
			L = F * X;
		int a = (int)L.ptr<double>(0)[0];
		int b = (int)L.ptr<double>(1)[0];
		int c = (int)L.ptr<double>(2)[0];
		int last = Rimage.cols;
		int d;
		int c;
		for (int x = 0; x < last; x++)
		{
			int y = (int)-(((a * x) + c) / b);
			//circle(Rimage,Point(x,y),1,Scalar(255,0,0),2);
			if (x == 0)
			{
				c = y;
			}
			if (x == (last - 1))
			{
				d = y;
			}
		}
		line(Rimage, Point(0, c), Point(last, d), Scalar(0, 0, 255)); // draws line from start cordinate (0,y) to (640,y)
		char c = waitKey(1);
		if (c == 27)
			break;
	}

	FundmentalMatrix();
	return 1;
}