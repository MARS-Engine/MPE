#include <MPE/engine_layer.hpp>
#include <MARS/engine/engine_worker.hpp>
#include <MPE/colliders/collider_base.hpp>

void mpe::mpe_update_layer_callback(mars_engine::layer_component_param&& _param) {
    auto start = _param.layers->begin() + _param.being;
    auto end = _param.layers->end();
    for (auto ptr = start; ptr < start + _param.length && ptr < end; ptr++) {
        auto target = static_cast<mpe_layer*>(ptr->target);
        target->mpe_update(*_param.layer_tick);

        auto collider = dynamic_cast<collider_base*>(target);

        if (collider == nullptr)
            return;

        for (auto ptr2 = ptr + 1; ptr2 < end; ptr2++) {
            auto next_collider = dynamic_cast<collider_base*>(static_cast<mpe_layer*>(ptr2->target));

            if (next_collider == nullptr)
                continue;

            if (collider->check_collision(next_collider))
                target->mpe_on_collide(next_collider);
        }
    }
}