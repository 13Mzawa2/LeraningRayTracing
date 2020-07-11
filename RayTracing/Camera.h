#pragma once
#include <opencv2/core.hpp>
#include <array>

namespace RayTracingCPU 
{
	class Camera 
	{
	public:
		Camera() = default;
		Camera(cv::Vec3d u, cv::Vec3d v, cv::Vec3d w)
			: eigenvecs({ u, v, w }) {};
		Camera(cv::Vec3d origin, cv::Vec3d lookat, cv::Vec3d viewup, double fov, double aspect);

	private:
		// カメラのワールド座標系原点
		cv::Vec3d cam_origin;
		// p = u e1 + v e2 + w e3 で表されるスクリーン平面の基底ベクトル e1, e2, e3
		std::array<cv::Vec3d, 3> eigenvecs;  
	};

}

