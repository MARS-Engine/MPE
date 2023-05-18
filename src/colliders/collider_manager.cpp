#include <MPE/colliders/collider_manager.hpp>
#include <MPE/colliders/collider_base.hpp>

using namespace mpe;

bool collider_manager::check_collision(collider_base *_left, collider_base *_right) {
    auto pair = std::pair(_left->get_type_index(), _right->get_type_index());

    auto callback = m_collider_callback.lock();

    if (!callback->contains(pair))
        return false;

    return callback->at(pair)(_left, _right);
}