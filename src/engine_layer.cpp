#include <MPE/engine_layer.hpp>
#include <MARS/engine/component.hpp>
#include <MPE/colliders/collider_base.hpp>

std::pair<mars_engine::engine_layer_component*, mars_engine::engine_layer_component*> mpe::mpe_update_layer_callback(mars_engine::engine_object* _target) {
    mars_engine::engine_layer_component* result = nullptr;
    mars_engine::engine_layer_component* tail = nullptr;

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

            while (_current->next != nullptr) {
                auto next_collider = dynamic_cast<collider_base*>((mpe_layer*)_current->next->target);
                _current = _current->next;

                if (next_collider == nullptr)
                    continue;

                if (collider->check_collision(next_collider))
                    target->mpe_on_collide(next_collider);
            }
        };

        if (result == nullptr) {
            result = new_component;
            tail = new_component;
        }
        else {
            tail->next = new_component;
            new_component->previous = tail;
            tail = new_component;
        }
    }

    return { result, tail };
}