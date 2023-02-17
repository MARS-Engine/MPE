#include <MPE/engine_layer.hpp>
#include <MARS/engine/component.hpp>

std::vector<std::function<void(void)>> mpe::mpe_update_layer_callback(mars_engine::engine_object* _target) {
    std::vector<std::function<void(void)>> result;
    for (auto& comp : _target->components()) {
        auto target = dynamic_cast<mpe_layer*>(comp);
        if (target != nullptr)
            result.emplace_back([target] { target->mpe_update(); });
    }

    return result;
}