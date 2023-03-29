#ifndef MPE_RIGID_BODY_
#define MPE_RIGID_BODY_

#include <MPE/engine_layer.hpp>
#include <MPE/colliders/collider_bridge.hpp>
#include <MARS/engine/component.hpp>

namespace mpe {

    class rigid_body : public mars_engine::component, public mpe_layer {
    private:
        float m_gravity = 9.8f;
        std::shared_ptr<collider_bridge> m_bridge;
    public:
        void on_set_object();
        
        void mpe_update(mars_engine::tick& _tick) override;
    };
}

#endif