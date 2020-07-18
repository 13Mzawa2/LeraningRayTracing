#include "Camera.h"

// ���_�C���ڈʒu�C������C��������p�C�A�X�y�N�g����w�肵�ăJ����������������
RayTracingCPU::Camera::Camera(cv::Vec3d origin, cv::Vec3d lookat, cv::Vec3d viewup, double fov, double aspect)
{
	this->cam_origin = origin;

	// �J�������K�������W�n�̊��XYZ���v�Z
	auto Z = cv::normalize(origin - lookat);  // ���ڈʒu����J�������_�Ɍ������x�N�g��
	auto X = cv::normalize(viewup.cross(Z));  // ������ƃJ�����������������镽�ʂɐ����ȃx�N�g��
	auto Y = Z.cross(X);

	// p = u*e1 + v*e2 + e3 ���C��ʒ��� = origin - Z = w/2 * e1 + h/2 * e2 + e3
	auto w = std::tan(fov / 2);
	auto h = w * aspect;
	eigenvecs[0] = 2 * w * X;
	eigenvecs[1] = -2 * h * Y;
	eigenvecs[2] = origin - Z - w / 2 * eigenvecs[0] - h / 2 * eigenvecs[1];

}

RayTracingCPU::Ray RayTracingCPU::Camera::getRay(cv::Vec2d uv)
{
	cv::Vec3d pos_on_screen = uv[0] * eigenvecs[0] + uv[1] * eigenvecs[1] + eigenvecs[2];
	
	return Ray(cam_origin, pos_on_screen-cam_origin);
}
