#ifndef MPE_LAYER_
#define MPE_LAYER_

#include <MARS/engine/engine_object.hpp>

namespace mpe {

    class mpe_layer {
    public:
        virtual void mpe_update() { }
    };

    std::vector<std::function<void()>> mpe_update_layer_callback(mars_engine::engine_object* _target);
}

#endif