#ifndef MPE_COLLIDER_BASE_
#define MPE_COLLIDER_BASE_

#include <MARS/engine/engine_handler.hpp>
#include <MARS/engine/component.hpp>
#include <MARS/loaders/mesh.hpp>
#include <MARS/engine/layers/main_layers.hpp>
#include <MPE/colliders/collider_manager.hpp>
#include <MPE/engine_layer.hpp>
#include <MPE/colliders/collider_bridge.hpp>
#include <typeindex>

namespace mpe {

    enum mpe_collider_type {
        MPE_COLLIDER_TYPE_COLLIDER,
        MPE_COLLIDER_TYPE_TRIGGER
    };

    struct collider_volume {
        mars_math::vector3<float> min_extent;
        mars_math::vector3<float> max_extent;

        collider_volume& operator*=(mars_math::matrix4<float> _left) {
            min_extent = (_left * mars_math::vector4<float>(min_extent, 1.0f)).xyz();
            max_extent = (_left * mars_math::vector4<float>(max_extent, 1.0f)).xyz();
            return *this;
        }
    };

    class collider_base : public mars_engine::component, public mpe_layer, public mars_layers::load_layer {
       protected:
           mpe_collider_type m_type = MPE_COLLIDER_TYPE_COLLIDER;
           collider_manager* m_manager = nullptr;
           std::type_index m_index = typeid(collider_base);
           collider_bridge* m_bridge = nullptr;
       public:
           [[nodiscard]] inline std::type_index get_type_index() const { return m_index; }

           explicit collider_base(std::type_index _index) { m_index = _index; }

           inline collider_bridge* get_collider_data() const { return m_bridge; }

           void on_set_object() override {
               m_bridge = object()->get_bridge<collider_bridge>("collider");
           }

           void load() override;

           virtual void load_from_mesh(mars_loader::mesh_base* _mesh) { }

           void set_collider_type(mpe_collider_type _type) { m_type = _type; }

           inline bool check_collision(collider_base* _other) { return m_manager->check_collision(this, _other); }

           void mpe_on_collide(collider_base* _other) override { }
       };
    }

#endif