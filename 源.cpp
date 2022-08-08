#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Point2f GetPicCord(double x,double y, double z) {

	cv::Mat K = (cv::Mat_<double>(3, 3)
		<< 1252.8131021185304, 0.0, 826.588114781398,
		0.0, 1252.8131021185304, 469.9846626224581,
		0, 0, 1);

	Mat XYZ = (Mat_<double>(3, 1) << x, y, z);

	double Zc = XYZ.at<double>(2, 0);
	cv::Mat uv_t = K * XYZ;
	cv::Point2f uv;
	uv.x = uv_t.at<double>(0, 0) / Zc;
	uv.y = uv_t.at<double>(1, 0) / Zc;

	return uv;
}


int main() {

	string pic = "n008-2018-08-01-15-16-36-0400__CAM_FRONT__1533151607012404.jpg";
	Mat src = imread(pic);

	vector<Point2f> points1;
	/*7.524, 15.000, 0.289
		7.287, 20.000, 0.596
		2.899, 30.000, 2.240
		- 3.223, 40.000, 4.339*/
	double xyz[4][3] = { 
		{7.524, 15.000, 0.289},
		{7.287, 20.000, 0.596},
		{2.899, 30.000, 2.240},
		{-3.223, 40.000, 4.339}
 };

	for (int m = 0; m < 4; m++) {
		Point2f p = GetPicCord(xyz[m][0], xyz[m][1], xyz[m][2]);

		printf("%d, %.3f,  %.3f\n", m, p.x, p.y);

		points1.push_back(p);
	}

	for (int i = 0; i < points1.size(); i++) {
		circle(src, points1[i], 3, Scalar(0, 255, 120), -1);//画点，其实就是实心圆
	}



	imshow("src", src); 

	waitKey(0);

	


	return 1;


	/*
	"cam_intrinsic": [[1252.8131021185304, 0.0, 826.588114781398], [0.0, 1252.8131021185304, 469.9846626224581], [0.0, 0.0, 1.0]]
	*/
}