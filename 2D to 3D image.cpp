#define _CRT_SECURE_NO_DEPRECATE
//core section, as here are defined the basic building blocks of the library

#include "opencv2/highgui/highgui.hpp" //highgui module, as this contains the functions for input and output operations
#include "opencv2/core/core.hpp"
#include <iostream> 
#include <stdlib.h>
#include <cmath> // for math functions
#define PI 3.14159265

using namespace cv;
using namespace std;
int rows=480; //it is globally declared because we know the size of rows 480;
int cols=640; //it is globally declared because we know the size of cols 640;
Mat depth;
Mat image;
Mat data3D;

void ColoredImage()
{
	
	image = imread("path/color.jpg"); 
	cout << image<<rows<<"X"<<cols;
}

void DepthImage() //since it is a .dat file which cannot be read by openCV we have to call it buy c
{
	
	depth.create(rows, cols, CV_16UC1); // allocates the space for .dat
	FILE *fp = fopen("path/depth.dat", "rb"); //fopen=function to perform operation such as read (rb), 
																//FILE= holds the information of the file of 'fopen'.
	fread(depth.data, 2, (rows*cols), fp); 

	cout << depth<<rows<<"X"<<cols;
	fclose(fp);
}

void Merg()
{
	int f = 524; //pixel
	int Cy = 256; //pixel
	int Cx = 312; //pixel
	int k = 0;  
	
	data3D.create(4, 480 * 640, CV_64FC1);

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			short int z = depth.ptr<short int>(y)[x];
			int y1 = image.ptr<uchar>(y)[x]; //picking up a perticular pixel
			int x1 = image.ptr<uchar>(y)[x]; //picking up a perticular pixel

			double Y = (double)((y1 / f) * z - (Cy * z)); //coverting pixel value to co-ordinates
			double X = (double)((x1 / f) * z - (Cx * z)); //coverting pixel value to co-ordinates

			data3D.ptr<double>(0)[k] = (double)X;
			data3D.ptr<double>(1)[k] = (double)Y;
			data3D.ptr<double>(2)[k] = (double)z;
			data3D.ptr<double>(3)[k] = 1;
			k++;

			cout << X << Y;
		}
	}
}
void Extrinsic()
{
	
	double degree;
	double c = 0.0;
	
	int Tx=0;
	int Ty=0;
	Mat data3D_new;
	String input;
	//Mat translation = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, 1, 0, Ty, 0, 0, 1, 0, 0, 0, 0, 1);
    //Extrinsic with rotation about x axis   
	//Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(b), -sin(b), Ty, 0, sin(b), cos(b), 0, 0, 0, 0, 1);
    //data3D_new = Extrinsic * data3D;
	cin >> input;
	if (input == "1") {
		c = c + 5;
		input = (c * PI / 180.0);//converting radient to degree
		Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(degree), -sin(degree), Ty, 0, sin(degree), cos(degree), 0, 0, 0, 0, 1);
		data3D_new = Extrinsic * data3D;
		
	}
	if (input == "2") {
		c = c - 5;
		input = (c * PI / 180.0);//converting radient to degree
		Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(degree), sin(degree), Ty, 0, -sin(degree), cos(degree), 0, 0, 0, 0, 1);
		data3D_new = Extrinsic * data3D;
	}
	if (input == "a") {
		Tx = Tx + 10;
		
		Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(degree), -sin(degree), Ty, 0, sin(degree), cos(degree), 0, 0, 0, 0, 1);
		data3D_new = Extrinsic * data3D;
	}
	if (input == "d") {
		Tx = Tx + 10;

		Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(degree), -sin(degree), Ty, 0, sin(degree), cos(degree), 0, 0, 0, 0, 1);
		data3D_new = Extrinsic * data3D;
	}
	if (input == "w") {
		Ty = Ty + 10;

		Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(degree), -sin(degree), Ty, 0, sin(degree), cos(degree), 0, 0, 0, 0, 1);
		data3D_new = Extrinsic * data3D;
	}
	if (input == "s") {
		Tx = Tx - 10;

		Mat Extrinsic = (Mat_<double>(4, 4) << 1, 0, 0, Tx, 0, cos(degree), -sin(degree), Ty, 0, sin(degree), cos(degree), 0, 0, 0, 0, 1);
		data3D_new = Extrinsic * data3D;
	}
}

int main()
{
	ColoredImage();
	DepthImage();
	Merg();
	Extrinsic();

	return 0;
}

