#pragma once
#include <opencv2/core.hpp>

namespace RayTracingCPU
{
	// 光線
	class Ray 
	{
	public:
		Ray() = default;
		Ray(cv::Vec3d &pos_, cv::Vec3d &dir_) :
			pos(pos_), dir(dir_) {};

		const cv::Vec3d& position() const { return pos; }
		const cv::Vec3d& direction() const { return dir; }
		cv::Vec3d at(double t) const { return pos + t * dir; }  // rayがtだけ進んだときの位置

	private:
		cv::Vec3d pos;	// 始点
		cv::Vec3d dir;	// 方向

	};
}
