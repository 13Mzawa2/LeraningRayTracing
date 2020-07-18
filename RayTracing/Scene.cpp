#include "Scene.h"

using namespace RayTracingCPU;

void RayTracingCPU::Scene::build()
{
	// Camera�̐���
	auto cam_origin = cv::Vec3d(0, 0, 0);
	auto lookat = cv::Vec3d(0, 0, -1);
	auto cam_up = cv::Vec3d(0, 1, 0);
	camera = Camera(cam_origin, lookat, cam_up, 60.0*CV_PI/180.0, (double)image.rows/image.cols);

	// world�̐���
	// ���̂͂����ɒǉ����Ă���
	world.add(std::make_shared<Sphere>(cv::Vec3d(0, 0, -3), 0.5));
	world.add(std::make_shared<Sphere>(cv::Vec3d(-1.5, 0, -5), 0.5));
	world.add(std::make_shared<Sphere>(cv::Vec3d(1.5, 0, 2), 0.5));
	world.add(std::make_shared<Sphere>(cv::Vec3d(0, -100.5, -1), 100.0)); 
}

void RayTracingCPU::Scene::render()
{
	// �`��iCPU���񏈗��D�t���O�����g�V�F�[�_�ɑ����j
	image.forEach<cv::Vec3d>([&](cv::Vec3d& v, const int* p) {
	//for (int h = 0; h < image.rows; ++h) {
	//	for (int w = 0; w < image.cols; ++w) {
	//		int p[2] = { h,w };
	//		auto& v = image.at<cv::Vec3d>(h, w);
			cv::Vec3d c(0.0);
			for (int i = 0; i < num_supersample; ++i) {
				cv::Vec2d uv = {
					double(p[1] + cv::theRNG().uniform(0.,1.)) / double(image.cols),
					double(p[0] + cv::theRNG().uniform(0.,1.)) / double(image.rows)
				};
				auto ray = camera.getRay(uv);
				c += getLambartColor(ray);
			}
			c = c / double(num_supersample);
			v = c;
	//	}
	//}
			});
	// �摜�̕\��
	cv::Mat img_8u;
	image.convertTo(img_8u, CV_8UC3, 255.0, 0);
	cv::imshow("test", img_8u);
	cv::waitKey();

}

cv::Vec3d RayTracingCPU::Scene::ambient(const Ray& r, const cv::Vec3d& skydir) const
{
	cv::Vec3d skycolor(1.0, 0.7, 0.5);
	cv::Vec3d basecolor(1.0, 1.0, 1.0);
	cv::Vec3d dir = r.direction();
	double cos_th = skydir.dot(dir) / cv::norm(skydir) / cv::norm(dir);
	double t = std::max(0.0, cos_th);
	cv::Vec3d color = skycolor * t + basecolor * (1 - t);
	return color;
}

cv::Vec3d RayTracingCPU::Scene::getColor(const Ray& r) const
{
	RayHitInfo hinfo;
	if (world.hit(r, 0, 1000.0, hinfo)) {
		return 0.5 * (hinfo.norm + cv::Vec3d({ 1.0,1.0,1.0}));
		//return cv::Scalar(0.0, 0.0, 1.0);
	}
	return ambient(r, cv::Vec3d(0.,1.,0.));
}

// �����o�[�g���˂̏ꍇ�C�g�U�p�x���̌��x�͖@�����������cos�Ō�������̂ŁC
// ���C�g���[�V���O�ł͂��̊m�����z�ɏ]���ă����_�����˂�����΃����o�[�g���˂��m���I�ɋߎ��ł���D
// ���̂Ƃ��m�����z�͖@���x�N�g���̑��ɐڂ�������ƈ�v����̂ŁC
// �@���x�N�g���̐悩�甼�a1�̋����̓_�������_���T���v�����@���x�N�g���ɉ����邱�Ƃ�
// �����o�[�g���˂ɏ]�������_�����˂������ł���D
cv::Vec3d RayTracingCPU::Scene::getLambartColor(const Ray& r) const
{
	RayHitInfo hinfo;

	if (world.hit(r, 1.0e-9, DBL_MAX, hinfo)) {
		// ���a1�C���S(0,0,0)�̓_�������_���T���v��
		cv::Vec3d randvec;
		do {
			cv::randu(randvec, -1.0, 1.0);
		} while (randvec.dot(randvec) > 1.0);
		// �����o�[�g���Ń����_�����˂���Ray�𐶐����Ď��̕����̐F�𓾂�
		return 0.5 * getLambartColor(Ray(hinfo.pos, hinfo.norm + randvec));
	}
	return ambient(r, cv::Vec3d(0., 1., 0.));
}
