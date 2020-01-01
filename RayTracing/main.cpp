#include<opencv2/opencv.hpp>
#ifdef _DEBUG
#define EXT_STR "d.lib"
#else
#define EXT_STR ".lib"
#endif

#define CV_VER_STR CVAUX_STR(CV_VERSION_MAJOR) CVAUX_STR(CV_VERSION_MINOR) CVAUX_STR(CV_VERSION_REVISION)
#pragma comment(lib, "opencv_world" CV_VER_STR EXT_STR)

void main()
{
	std::cout << "hello, world" << std::endl;

	cv::Mat img(480, 640, CV_8UC3);
	img.forEach<cv::Vec3b>([&](cv::Vec3b &v, const int *p){
		v[0] = (uchar)(p[0] / 480. * 255.);
		v[1] = (uchar)(p[1] / 640. * 255.);
		v[2] = 0;
	});
	cv::imshow("test", img);
	cv::waitKey();

	return;
}