#include "Scene.h"

using namespace RayTracingCPU;

void RayTracingCPU::Scene::build()
{
	// Cameraの生成
	auto cam_origin = cv::Vec3d(0, 0, 0);
	auto lookat = cv::Vec3d(0, 0, -1);
	auto cam_up = cv::Vec3d(0, 1, 0);
	camera = Camera(cam_origin, lookat, cam_up, 60.0*CV_PI/180.0, (double)image.rows/image.cols);
	//camera = Camera(
	//	cv::Vec3d(-2.0, -1.0, -1.0),
	//	cv::Vec3d(4.0, 0.0, 0.0),
	//	cv::Vec3d(0.0, 2.0, 0.0)
	//);

	// worldの生成
	// 物体はここに追加していく
	world.add(std::make_shared<Sphere>(cv::Vec3d(0, 0, -5), 0.5));
	world.add(std::make_shared<Sphere>(cv::Vec3d(0, -100.5, -1), 100.0)); 
}

void RayTracingCPU::Scene::render()
{
	// 描画（CPU並列処理．フラグメントシェーダに相当）
	image.forEach<cv::Vec3b>([&](cv::Vec3b& v, const int* p) {
		cv::Vec2d uv = { double(p[1]) / image.cols, double(p[0]) / image.rows };
		auto ray = camera.getRay(uv);
		auto c = getColor(ray);

		v[0] = (uchar)(c[0] * 255.);
		v[1] = (uchar)(c[1] * 255.);
		v[2] = (uchar)(c[2] * 255.);
	});
	// 画像の表示
	cv::imshow("test", image);
	cv::waitKey();
	
}

cv::Scalar RayTracingCPU::Scene::ambient(const Ray& r, const cv::Vec3d& viewup) const
{
	cv::Scalar skycolor(1.0, 0.7, 0.5);
	cv::Scalar basecolor(1.0, 1.0, 1.0);
	cv::Vec3d dir = r.direction();
	double cos_th = viewup.dot(dir) / cv::norm(viewup) / cv::norm(dir);
	double t = std::max(0.0, cos_th);
	cv::Scalar color = skycolor * t + basecolor * (1 - t);
	return color;
}

cv::Scalar RayTracingCPU::Scene::getColor(const Ray& r) const
{
	RayHitInfo hinfo;
	if (world.hit(r, 0, 1000, hinfo)) {
		return 0.5 * (hinfo.norm + cv::Vec3d({ 1.0,1.0,1.0}));
		//return cv::Scalar(0.0, 0.0, 1.0);
	}
	return ambient(r, cv::Vec3d(0,1,0));
}
