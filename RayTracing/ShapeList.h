#pragma once
#include "Shape.h"
#include <vector>
#include <memory>

namespace RayTracingCPU
{
    // Shapeクラスの実体をコピーせずに共有して所有させるために用いる．
    // sheared pointerにすることでインスタンスが共有されるので，
    // Shape内での変更がShapeListにも反映される．
    typedef std::shared_ptr<Shape> ShapePtr; 

    // 複数の物体を管理するクラス
    class ShapeList :
        public Shape
    {
    private:
        std::vector<ShapePtr> shapes;

    public:
        ShapeList() = default;

        int size() { return shapes.size(); }

        // 物体の追加
        void add(const ShapePtr& shape) {
            shapes.push_back(shape);
        }
        
        // ShapeListが保持する物体群との衝突判定
        // 最もRay原点に近い表面での衝突情報を返す
        virtual bool hit(const Ray& r, double t0, double t1, RayHitInfo& hinfo) const override {
            RayHitInfo info_temp;
            bool hit_anything = false;
            double t_closest = t1;
            for (auto& p : shapes) {
                // より近い物体との衝突位置を割り出すため，
                // それまでで最もRay原点に近い衝突位置までの範囲で衝突判定
                if (p->hit(r, t0, t_closest, info_temp)) {
                    hit_anything = true;
                    t_closest = info_temp.t;
                    hinfo = info_temp;
                }
            }
            return hit_anything;
        }
    };
}
