#ifndef MPE_AABB_
#define MPE_AABB_

#include <MARS/math/vector3.hpp>
#include "collider_base.hpp"

namespace mpe {

    bool aabb_aabb_collision_check(collider_base* _left, collider_base* _right);

    class AABB : public collider_base {
    private:
        collider_volume m_volume;
    public:
        AABB() : collider_base(typeid(AABB)) { }

        [[nodiscard]] inline collider_volume get_volume() const { return m_volume; }

        void load_from_mesh(const std::shared_ptr<mars_loader::mesh_base>& _mesh) override;

        void load() override;
        void mpe_on_collide(collider_base *_other) override;
    };
}

#endif