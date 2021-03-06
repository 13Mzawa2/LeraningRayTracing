#pragma once
#include "RayTracingCPU.h"
#include <random>

namespace RayTracingCPU
{
	// レンダリング対象のシーン
	class Scene
	{
	private:
		Camera		camera;
		cv::Mat		image;   // 64bit,3chの画像
		ShapeList	world;
		cv::RNG		rng;
		cv::Mat		gamma_lut;
		static const int num_supersample = 5;

	public:
		Scene(int width, int height) 
			: image(cv::Mat(cv::Size(width, height), CV_64FC3, cv::Scalar::all(0.2))) {};

		void build();
		void render();
		cv::Mat developPhoto(cv::Mat& raw);
		cv::Vec3d ambient(const Ray& r, const cv::Vec3d& skydir) ;
		cv::Vec3d getColor(const Ray& r) ;
		cv::Vec3d getLambartColor(const Ray& r) ;
	};

}

// メモ
// type func(const type& variable) const
// のように，メンバ関数の後ろにconstをつけると，関数がconstメンバ関数となる．
// このとき，呼び出したオブジェクトの持つメンバ変数がconstになってくれるので，
// 引数variableのメンバ変数がconst化する．
// 「オブジェクトにメンバ関数と互換性のない型修飾子があります」のエラー原因は大抵これ．
