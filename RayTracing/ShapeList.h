#pragma once
#include "Shape.h"
#include <vector>
#include <memory>

namespace RayTracingCPU
{
    // Shape�N���X�̎��̂��R�s�[�����ɋ��L���ď��L�����邽�߂ɗp����D
    // sheared pointer�ɂ��邱�ƂŃC���X�^���X�����L�����̂ŁC
    // Shape���ł̕ύX��ShapeList�ɂ����f�����D
    typedef std::shared_ptr<Shape> ShapePtr; 

    // �����̕��̂��Ǘ�����N���X
    class ShapeList :
        public Shape
    {
    private:
        std::vector<ShapePtr> shapes;

    public:
        ShapeList() = default;

        int size() { return shapes.size(); }

        // ���̂̒ǉ�
        void add(const ShapePtr& shape) {
            shapes.push_back(shape);
        }
        
        // ShapeList���ێ����镨�̌Q�Ƃ̏Փ˔���
        // �ł�Ray���_�ɋ߂��\�ʂł̏Փˏ���Ԃ�
        virtual bool hit(const Ray& r, double t0, double t1, RayHitInfo& hinfo) const override {
            RayHitInfo info_temp;
            bool hit_anything = false;
            double t_closest = t1;
            for (auto& p : shapes) {
                // ���߂����̂Ƃ̏Փˈʒu������o�����߁C
                // ����܂łōł�Ray���_�ɋ߂��Փˈʒu�܂ł͈̔͂ŏՓ˔���
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
