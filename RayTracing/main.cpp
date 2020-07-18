#include<opencv2/opencv.hpp>

#include "RayTracingCPU.h"

using namespace RayTracingCPU;

void main()
{
	std::cout << "hello, world" << std::endl;
	// OpenCV‚Ì—”¶¬Ší‚ð‰Šú‰»
	cv::theRNG().state = std::random_device{}();
	cv::Vec3d r;
	std::cout << r.randu(0.0, 1.0) << std::endl;
	std::cout << r.randu(0.0, 1.0) << std::endl;

	Scene scene(640, 480);
	scene.build();
	scene.render();

	return;
}