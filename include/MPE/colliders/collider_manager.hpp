#ifndef MPE_COLLIDER_MANAGER_
#define MPE_COLLIDER_MANAGER_

#include <MARS/engine/singleton.hpp>
#include <pl/safe_map.hpp>
#include <functional>
#include <set>
#include <typeindex>

namespace mpe {

    class collider_base;

    class collider_manager : public mars_engine::singleton {
    private:
        pl::safe_map<std::pair<std::type_index, std::type_index>, std::function<bool(collider_base*, collider_base*)>> m_collider_callback;
    public:
        using mars_engine::singleton::singleton;

        bool check_collision(collider_base* _left, collider_base* _right);

        template<typename A, typename B> void add_collision_checker(const std::function<bool(collider_base*, collider_base*)>& _callback) {
            auto pair = std::pair(std::type_index(typeid(A)), std::type_index(typeid(B)));

            //cheap check to see if already exists since 99% of the time it will already exist
            if (m_collider_callback.contains(pair))
                return;

            //expensive check because it needs to lock to make 100% sure it doesn't already exist
            m_collider_callback.lock();

            if (m_collider_callback.contains(pair))
                return m_collider_callback.unlock();

            m_collider_callback.insert(std::pair(pair, _callback));
            m_collider_callback.unlock();
        }
    };
}

#endif