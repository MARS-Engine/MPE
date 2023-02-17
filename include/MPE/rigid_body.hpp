#ifndef MPE_RIGID_BODY_
#define MPE_RIGID_BODY_

#include <MPE/engine_layer.hpp>
#include <MARS/engine/component.hpp>

namespace mpe {

    class rigid_body : public mars_engine::component, public mpe_layer {
    private:
        float m_gravity = 9.8f;
    public:

        void mpe_update() override;
    };
}

#endif