#include <MPE/engine_layer.hpp>
#include <MARS/engine/engine_worker.hpp>
#include <MPE/colliders/collider_base.hpp>

void mpe::mpe_update_layer_callback(mars_engine::layer_component_param&& _param) {
    for (auto i = 0; i < _param.length; i++) {
        auto target = static_cast<mpe_layer*>(_param.layers[i].target);
        target->mpe_update(*_param.layer_tick);

        auto collider = dynamic_cast<collider_base*>(target);

        if (collider == nullptr)
            return;

        for (auto i2 = i + 1; i2 < _param.layer_size - _param.offset; i2++) {
            auto next_collider = dynamic_cast<collider_base*>(static_cast<mpe_layer*>(_param.layers[i2].target));

            if (next_collider == nullptr)
                continue;

            if (collider->check_collision(next_collider))
                target->mpe_on_collide(next_collider);
        }
    }
}