#ifndef MPE_LAYER_
#define MPE_LAYER_

#include <MARS/engine/mars_object.hpp>
#include <MARS/engine/object_engine.hpp>
#include <MARS/engine/component.hpp>

namespace mpe {
    class collider_base;

    class mpe_layer {
    public:
        virtual void mpe_update(mars_engine::tick& _tick) {  }

        virtual void mpe_on_collide(collider_base* _other) { }
    };

    void mpe_update_layer_callback(const mars_engine::layer_component_param& _param);
    bool mpe_update_layer_validator(const mars_ref<mars_engine::component>& _target, mars_engine::engine_layer_component& _val);
}

#endif