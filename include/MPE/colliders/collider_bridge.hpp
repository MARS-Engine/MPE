#ifndef MPE_COLLIDER_BRIDGE_
#define MPE_COLLIDER_BRIDGE_

#include <MARS/math/vector3.hpp>
#include <MARS/engine/object_engine.hpp>
#include <MARS/engine/bridge.hpp>

namespace mpe {

    class collider_bridge : public mars_engine::bridge {
    private:
        mars_math::vector3<float> m_velocity;
        mars_math::vector3<float> m_acceleration;
        float m_terminal_acceleration = 9.8f;
        float m_mass;
    public:
        using mars_engine::bridge::bridge;

        inline void accelerate(const mars_math::vector3<float>& _acceleration) { m_acceleration += _acceleration; m_acceleration.clamp(-m_terminal_acceleration, m_terminal_acceleration); }

        inline void update_velocity(float _delta_time) {
            auto acceleration = m_acceleration * _delta_time;
            m_acceleration -= acceleration;
            m_velocity += m_acceleration;
            m_velocity.clamp(-m_terminal_acceleration, m_terminal_acceleration);
        }

        [[nodiscard]] inline float mass() const { return m_mass; }

        [[nodiscard]] inline mars_math::vector3<float> velocity() const { return m_velocity; }
        [[nodiscard]] inline mars_math::vector3<float> delta_velocity(float _delta_time) const { return m_velocity * _delta_time; }

        [[nodiscard]] inline mars_math::vector3<float> acceleration() const { return m_acceleration; }
        [[nodiscard]] inline mars_math::vector3<float> delta_acceleration(float _delta_time) const { return m_acceleration * _delta_time; }
    };
}

#endif