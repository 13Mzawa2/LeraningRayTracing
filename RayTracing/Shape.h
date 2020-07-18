#pragma once

#include <opencv2/opencv.hpp>
#include "Ray.h"

namespace RayTracingCPU
{
	// Rayが物体に衝突したときの情報を格納するクラス
	class RayHitInfo
	{
	public:
		double t;		// 衝突時のRayのパラメータ
		cv::Vec3d pos;  // 衝突位置
		cv::Vec3d norm; // 衝突位置での法線ベクトル
	};

	// 形状情報の抽象クラス
	class Shape
	{
	public:
		// t0からt1の範囲内で，Rayが物体に衝突するかを判定
		virtual bool hit(const Ray& r, double t0, double t1, RayHitInfo& hinfo) const = 0;
	};

}