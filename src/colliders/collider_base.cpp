#include <MPE/colliders/collider_base.hpp>

using namespace mpe;

void collider_base::load() {
    m_manager = engine()->get<collider_manager>();
}