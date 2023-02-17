#ifndef MPE_COLLIDER_BASE_
#define MPE_COLLIDER_BASE_

#include <MARS/engine/component.hpp>
#include <MPE/engine_layer.hpp>

namespace mpe {

    enum mpe_collider_type {
        MPE_COLLIDER_TYPE_COLLIDER,
        MPE_COLLIDER_TYPE_TRIGGER
    };

    class collider_base : public mars_engine::component, public mpe_layer {
    private:
        mpe_collider_type m_type = MPE_COLLIDER_TYPE_COLLIDER;
    public:

        void mpe_update() override;
        void set_collider_type(mpe_collider_type _type) { m_type = _type; }
    };
}

#endif