#pragma once
#include "RayTracingCPU.h"

namespace RayTracingCPU
{
	// レンダリング対象のシーン
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

// メモ
// type func(const type& variable) const
// のように，メンバ関数の後ろにconstをつけると，関数がconstメンバ関数となる．
// このとき，呼び出したオブジェクトの持つメンバ変数がconstになってくれるので，
// 引数variableのメンバ変数がconst化する．
// 「オブジェクトにメンバ関数と互換性のない型修飾子があります」のエラー原因は大抵これ．
