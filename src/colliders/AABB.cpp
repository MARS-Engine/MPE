#include <MPE/colliders/AABB.hpp>

using namespace mpe;

bool mpe::aabb_aabb_collision_check(collider_base* _left, collider_base* _right) {
    auto left = dynamic_cast<AABB*>(_left);
    auto right = dynamic_cast<AABB*>(_right);

    auto lvol = left->get_volume();
    auto rvol = right->get_volume();

    lvol *= _left->transform().matrix();
    rvol *= _right->transform().matrix();

    return (
            lvol.min_extent.x() <= rvol.max_extent.x() &&
            lvol.max_extent.x() >= rvol.min_extent.x() &&
            lvol.min_extent.y() <= rvol.max_extent.y() &&
            lvol.max_extent.y() >= rvol.min_extent.y() &&
            lvol.min_extent.z() <= rvol.max_extent.z() &&
            lvol.max_extent.z() >= rvol.min_extent.z()
            );
}

void AABB::load() {
    collider_base::load();
    m_manager->add_collision_checker<AABB, AABB>(aabb_aabb_collision_check);
}

void AABB::load_from_mesh(mars_loader::mesh_base* _mesh) {
    m_volume = {
            _mesh->volume.min_extent,
            _mesh->volume.max_extent
    };
}

void AABB::mpe_on_collide(collider_base *_other) {
    static const mars_math::vector3<float> faces[6] = {
            { -1,  0,  0 }, {  1,  0,  0 },
            {  0, -1,  0 }, {  0,  1,  0 },
            {  0,  0, -1 }, {  0,  0,  1 }
    };

    auto lvol = dynamic_cast<AABB*>(_other)->get_volume();
    auto rvol = get_volume();

    lvol *= transform().matrix();
    rvol *= _other->transform().matrix();

    float distances[6] = {
            (rvol.max_extent.x() - lvol.min_extent.x()),
            (lvol.max_extent.x() - rvol.min_extent.x()),
            (rvol.max_extent.y() - lvol.min_extent.y()),
            (lvol.max_extent.y() - rvol.min_extent.y()),
            (rvol.max_extent.z() - lvol.min_extent.z()),
            (lvol.max_extent.z() - rvol.min_extent.z())
    };

    float penetration = FLT_MAX;
    mars_math::vector3<float> best_axis;

    for (size_t i = 0; i < 6; i++) {
        if (distances[i] >= penetration)
            continue;

        penetration = distances[i];
        best_axis = faces[i];
    }
    penetration /= 2.0f;

    transform().set_position(transform().position() - (best_axis * penetration));
}