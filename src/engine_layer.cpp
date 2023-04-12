#include <MPE/engine_layer.hpp>
#include <MARS/engine/engine_worker.hpp>
#include <MPE/colliders/collider_base.hpp>

void mpe::mpe_update_layer_callback(const mars_engine::layer_component_param &_param) {
    std::atomic<size_t>& index = _param._worker->get_index();
    for (size_t i = index.fetch_add(1); i < _param.layers->size(); i = index.fetch_add(1)) {
        auto target = static_cast<mpe_layer*>(_param.layers->at(i).target);
        target->mpe_update(*_param.layer_tick);

        auto collider = dynamic_cast<collider_base*>(target);

        if (collider == nullptr)
            return;

        for (size_t i2 = i + 1; i2 < _param.layers->size(); i2++) {
            auto next_collider = dynamic_cast<collider_base*>((mpe_layer*)_param.layers->at(i2).target);

            if (next_collider == nullptr)
                continue;

            if (collider->check_collision(next_collider))
                target->mpe_on_collide(next_collider);
        }
    }
}