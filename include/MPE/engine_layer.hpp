#ifndef MPE_LAYER_
#define MPE_LAYER_

#include <MARS/engine/engine_object.hpp>
#include <MARS/engine/engine_handler.hpp>

namespace mpe {
    class collider_base;

    class mpe_layer {
    public:
        virtual void mpe_update() {  }

        virtual void mpe_on_collide(collider_base* _other) { }
    };

    std::pair<mars_engine::engine_layer_component*, mars_engine::engine_layer_component*> mpe_update_layer_callback(mars_engine::engine_object* _target);
}

#endif