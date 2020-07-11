#pragma once
#include <opencv2/core.hpp>

namespace RayTracingCPU
{
	class Ray 
	{
	public:
		Ray() = default;
		Ray(cv::Vec3d &pos_, cv::Vec3d &dir_) :
			pos(pos_), dir(dir_) {};

		const cv::Vec3d& position() { return pos; }
		const cv::Vec3d& direction() { return dir; }
		cv::Vec3d at(double t) { return pos + t * dir; }

	private:
		cv::Vec3d pos;
		cv::Vec3d dir;

	};
}
