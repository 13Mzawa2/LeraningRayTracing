#include "Camera.h"

// 原点，注目位置，上方向，水平視野角，アスペクト比を指定してカメラを初期化する
RayTracingCPU::Camera::Camera(cv::Vec3d origin, cv::Vec3d lookat, cv::Vec3d viewup, double fov, double aspect)
{
	this->cam_origin = origin;

	// カメラ正規直交座標系の基底XYZを計算
	auto Z = cv::normalize(origin - lookat);  // 注目位置からカメラ原点に向かうベクトル
	auto X = cv::normalize(viewup.cross(Z));  // 上方向とカメラ光軸方向が張る平面に垂直なベクトル
	auto Y = Z.cross(X);

	// p = u*e1 + v*e2 + e3 より，画面中央 = origin - Z = w/2 * e1 + h/2 * e2 + e3
	auto halfW = std::tan(fov / 2.);
	auto halfH = halfW * aspect;
	eigenvecs[0] = 2.*halfW * X;
	eigenvecs[1] = -2.*halfH * Y;
	eigenvecs[2] = origin - Z - halfW * eigenvecs[0] - halfH * eigenvecs[1];

}

RayTracingCPU::Ray RayTracingCPU::Camera::getRay(cv::Vec2d uv)
{
	return Ray(cam_origin, uv[0] * eigenvecs[0] + uv[1] * eigenvecs[1] + eigenvecs[2] - cam_origin);
}
