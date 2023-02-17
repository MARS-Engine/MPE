#include <MPE/rigid_body.hpp>

using namespace mpe;

void rigid_body::mpe_update() {
    transform().set_position(transform().position() + mars_math::vector3(0.0f, -m_gravity * get_delta_time(), 0.0f));
}