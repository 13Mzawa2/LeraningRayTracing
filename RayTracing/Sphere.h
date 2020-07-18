#pragma once
#include "Shape.h"

namespace RayTracingCPU
{
    class Sphere :
        public Shape
    {
    private:
        cv::Vec3d center;
        double radius;

    public:
        Sphere() = default;
        Sphere(const cv::Vec3d c, double r)
            : center(c), radius(r) {}

        // 球面とRayの衝突判定はtに関する二次方程式になる
        // p = o + t*d, (p - c).dot(p - c) = r^2
        // -> |d|^2 * t^2 + 2*d.dot(o - c) * t + |o - c|^2 = 0
        inline virtual bool hit(const Ray& r, double t0, double t1, RayHitInfo& info) const override {
            auto co = r.position() - center;
            auto a = r.direction().dot(r.direction());
            auto b = 2. * co.dot(r.direction());
            auto c = co.dot(co) - radius * radius;
            auto det = b * b - 4. * a * c;
            if (det > 0.0) {
                auto root_D = std::sqrt(det);
                // Ray原点側からチェック
                // 探索範囲内で衝突したらhit情報を返す
                auto t_near = (-b - root_D) / (2.0 * a);
                if (t_near > t0 && t_near < t1) {
                    info.t = t_near;
                    info.pos = r.at(t_near);
                    info.norm = (info.pos - center)/radius;
                    return true;
                }
                auto t_far = (-b + root_D) / (2.0 * a);
                if (t_far > t0 && t_far < t1) {
                    info.t = t_far;
                    info.pos = r.at(t_far);
                    info.norm = (info.pos - center)/radius;
                    return true;
                }
            }
            return false;
        }
    };
}

