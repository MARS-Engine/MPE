#ifndef MPE_COLLIDER_BRIDGE_
#define MPE_COLLIDER_BRIDGE_

#include <MARS/engine/object_bridge.hpp>
#include <MARS/math/vector3.hpp>
#include <MARS/engine/engine_handler.hpp>

namespace mpe {

    class collider_bridge : public mars_engine::object_bridge {
    private:
        mars_math::vector3<float> m_velocity;
        mars_math::vector3<float> m_acceleration;
        float m_terminal_acceleration = 9.8f;
        float m_mass;
    public:
        using mars_engine::object_bridge::object_bridge;

        inline void accelerate(const mars_math::vector3<float>& _acceleration) { m_acceleration += _acceleration; m_acceleration.clamp(-m_terminal_acceleration, m_terminal_acceleration); }

        inline void update_velocity() {
            auto acceleration = m_acceleration * get_engine_object()->engine()->get_delta_time();
            m_acceleration -= acceleration;
            m_velocity += m_acceleration;
            m_velocity.clamp(-m_terminal_acceleration, m_terminal_acceleration);
        }

        [[nodiscard]] inline float mass() const { return m_mass; }

        [[nodiscard]] inline mars_math::vector3<float> velocity() const { return m_velocity; }
        [[nodiscard]] inline mars_math::vector3<float> delta_velocity() const { return m_velocity * get_engine_object()->engine()->get_delta_time(); }

        [[nodiscard]] inline mars_math::vector3<float> acceleration() const { return m_acceleration; }
        [[nodiscard]] inline mars_math::vector3<float> delta_acceleration() const { return m_acceleration * get_engine_object()->engine()->get_delta_time(); }
    };
}

#endif