#include <MPE/engine_layer.hpp>
#include <MARS/engine/component.hpp>
#include <MPE/colliders/collider_base.hpp>

std::vector<mars_engine::engine_layer_component> mpe::mpe_update_layer_callback(const mars_engine::mars_object& _target) {
    std::vector<mars_engine::engine_layer_component> list;

    for (auto& comp : _target->components()) {
        auto target = dynamic_cast<mpe_layer*>(comp.get());
        if (target == nullptr)
            continue;

        auto new_component = mars_engine::engine_layer_component();
        new_component.target = target;
        new_component.parent = &_target;

        new_component.callback = [](const mars_engine::layer_component_param& _param){
            auto target = static_cast<mpe_layer*>(_param.component->target);
            target->mpe_update(*_param.layer_tick);

            auto collider = dynamic_cast<collider_base*>(target);

            if (collider == nullptr)
                return;

            for (size_t i = _param.index + 1; i < _param.layers->size(); i++) {
                auto next_collider = dynamic_cast<collider_base*>((mpe_layer*)_param.layers->at(i).target);

                if (next_collider == nullptr)
                    continue;

                if (collider->check_collision(next_collider))
                    target->mpe_on_collide(next_collider);
            }
        };

        list.push_back(new_component);
    }

    return list;
}