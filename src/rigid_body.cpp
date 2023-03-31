#include <MPE/rigid_body.hpp>

using namespace mpe;

void rigid_body::on_set_object() {
    m_bridge = object()->get_bridge<collider_bridge>("collider");
}

void rigid_body::mpe_update(mars_engine::tick& _tick) {
    m_bridge->accelerate({ 0, -m_gravity, 0 });
    m_bridge->update_velocity(_tick.delta());
    transform().set_position(transform().position() + m_bridge->delta_velocity(_tick.delta()));
}