#pragma once
#include "opencv2/highgui/highgui.hpp" //highgui module, as this contains the functions for input and output operations
#include "opencv2/core/core.hpp"
#include <iostream>
#include <stdlib.h>
#include <opencv2\imgproc.hpp>
using namespace cv;
using namespace std;
Mat img;
Mat img_i;
int w = 20;
int value_of_w;
Point left_corner;
void getIntegral(Mat& img, Mat& img_i) //this will get integral function
{
	//create the img_i
	img_i.create(img.rows, img.cols, CV_64FC1); //double to hold the integral values
	//Traverse each pixel in the img_i and assign a value for it
	for (int y = 0; y < img_i.rows; y++)
	{
		for (int x = 0; x < img_i.cols; x++)
		{
			double sum = 0.0;
			for (int y_i = 0; y_i <= y; y_i++)
			{
				for (int x_i = 0; x_i <= x; x_i++)
				{
					sum += (double)img.ptr<uchar>(y_i)[x_i];
				}
			}
			img_i.ptr<double>(y)[x] = sum;
		}
	}
}
int getSum(Point P1, Point P2, Mat& img_i)
{
	int sum = 0;
	int x1 = P1.x;
	int y1 = P1.y;
	int x2 = P2.x;
	int y2 = P2.y;
	double A = img_i.ptr<double>[y1](x1);
	double B = img_i.ptr<double>[y1](x1 + w);
	double C = img_i.ptr<double>[y1 + w](x1);
	double D = img_i.ptr<double>[y2](x2);
	int sum = (int)(A + D - B - C);
	return sum;
}
int average(int sum1, int sum2)
{
	int answer = (sum1 - sum2) / (w * w);
	return answer;
}
void draw(Point left, int w) //draw the line arround the received value
{
	Point end1, end2, end3;
	end1.x = left.x + w;
	end1.y = left.y;
	end2.x = left.x + w;
	end2.y = left.y + 2 * w;
	end3.x = left.x;
	end3.y = left.y + 2 * w;
	line(img, left, end1, (0, 0, 255), 3);
	line(img, end1, end2, (0, 0, 255), 3);
	line(img, end2, end3, (0, 0, 255), 3);
	line(img, end3, left, (0, 0, 255), 3);
}
int main()
{
	img = imread("C:/Users/19378/Desktop/img2.jpg", 0);
	getIntegral(img, img_i);
	int k1 = img.rows / 3;
	while (w < k1)
	{
		for (int i = 0; i < img.rows; i += (i + 1)*w / 10)
		{
			for (int j = 0; j < img.cols; j += (j + 1)*w / 10)
			{
				Point pt1 = Point(i, j);
				Point pt2 = Point(i + w, j + w);
				int sum1 = getSum(pt1, pt2, img_i);
				Point pt3 = Point();
				Point pt4 = Point();
				int sum2 = getSum(pt3, pt4, img_i);
				int avg = average(sum1, sum2);
				if (avg == 0) //if the avg 0; means the points are received
				{
					value_of_w = w;
					left_corner.x = i;
					left_corner.y = j;
					draw(left_corner, w);
					break;
				}
			}
		}
		w = 1.2 * w;
	}
	while (1)
	{
		imshow("Image", img);
		char c = waitKey(500); //every 1 ms, opencv will check the keyboard event
		if (c == 27) //if the key is ESc is hit
			break;
	}
}
