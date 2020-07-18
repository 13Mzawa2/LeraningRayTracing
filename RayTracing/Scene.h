#pragma once
#include "RayTracingCPU.h"

namespace RayTracingCPU
{
	// �����_�����O�Ώۂ̃V�[��
	class Scene
	{
	private:
		Camera   camera;
		cv::Mat   image;
		ShapeList world;

	public:
		Scene(int width, int height) 
			: image(cv::Mat(cv::Size(width, height), CV_8UC3, cv::Scalar::all(0.2))) {};

		void build();
		void render();
		cv::Scalar ambient(const Ray& r, const cv::Vec3d& viewup) const;
		cv::Scalar getColor(const Ray& r) const;
	};

}

// ����
// type func(const type& variable) const
// �̂悤�ɁC�����o�֐��̌���const������ƁC�֐���const�����o�֐��ƂȂ�D
// ���̂Ƃ��C�Ăяo�����I�u�W�F�N�g�̎������o�ϐ���const�ɂȂ��Ă����̂ŁC
// ����variable�̃����o�ϐ���const������D
// �u�I�u�W�F�N�g�Ƀ����o�֐��ƌ݊����̂Ȃ��^�C���q������܂��v�̃G���[�����͑���D
