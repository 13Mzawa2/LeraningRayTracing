#pragma once

#include <opencv2/opencv.hpp>
#include "Ray.h"

namespace RayTracingCPU
{
	// Ray�����̂ɏՓ˂����Ƃ��̏����i�[����N���X
	class RayHitInfo
	{
	public:
		double t;		// �Փˎ���Ray�̃p�����[�^
		cv::Vec3d pos;  // �Փˈʒu
		cv::Vec3d norm; // �Փˈʒu�ł̖@���x�N�g��
	};

	// �`����̒��ۃN���X
	class Shape
	{
	public:
		// t0����t1�͈͓̔��ŁCRay�����̂ɏՓ˂��邩�𔻒�
		virtual bool hit(const Ray& r, double t0, double t1, RayHitInfo& hinfo) const = 0;
	};

}