#include<opencv2/opencv.hpp>

#include "RayTracingCPU.h"

using namespace RayTracingCPU;

void main()
{
	std::cout << "hello, world" << std::endl;

	Scene scene(640, 480);
	scene.build();
	scene.render();

	return;
}