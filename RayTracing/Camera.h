#pragma once
#include <opencv2/core.hpp>
#include <array>
#include "Ray.h"

namespace RayTracingCPU 
{
	// �J����
	// X: �������CY: ������CZ: ��ʑO�������Ƃ���D
	// �X�N���[�����ʍ��W�n u,v �́C��������_�Ƃ���D
	class Camera 
	{
	public:
		Camera() = default;
		Camera(cv::Vec3d u, cv::Vec3d v, cv::Vec3d w)
			: eigenvecs({ u, v, w }) {};
		Camera(cv::Vec3d origin, cv::Vec3d lookat, cv::Vec3d viewup, double fov, double aspect);
		Ray getRay(cv::Vec2d uv);

	private:
		// �J�����̃��[���h���W�n���_
		cv::Vec3d cam_origin;
		// p = u e1 + v e2 + e3 �ŕ\�����X�N���[�����ʂ̊��x�N�g�� e1, e2, e3
		std::array<cv::Vec3d, 3> eigenvecs;  
	};

}

