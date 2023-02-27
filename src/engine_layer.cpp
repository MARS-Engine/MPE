#include <MPE/engine_layer.hpp>
#include <MARS/engine/component.hpp>
#include <MPE/colliders/collider_base.hpp>

std::vector<mars_engine::engine_layer_component*> mpe::mpe_update_layer_callback(mars_engine::engine_object* _target) {
    std::vector<mars_engine::engine_layer_component*> list;

    for (auto& comp : _target->components()) {
        auto target = dynamic_cast<mpe_layer*>(comp);
        if (target == nullptr)
            continue;

        auto new_component = new mars_engine::engine_layer_component();
        new_component->target = target;
        new_component->parent = _target;

        new_component->callback = [target](mars_engine::engine_layer_component* _current){
            target->mpe_update();

            auto collider = dynamic_cast<collider_base*>(target);

            if (collider == nullptr)
                return;

            auto next = _current->next;

            while (next != nullptr) {
                auto next_collider = dynamic_cast<collider_base*>((mpe_layer*)next->target);
                next = next->next;

                if (next_collider == nullptr)
                    continue;

                if (collider->check_collision(next_collider))
                    target->mpe_on_collide(next_collider);
            }
        };

        if (!list.empty())
            list[list.size() - 1]->next = new_component;

        list.push_back(new_component);
    }

    return list;
}