#ifndef MPE_AABB_
#define MPE_AABB_

#include <MARS/math/vector3.hpp>
#include "collider_base.hpp"

namespace mpe {

    struct collider_volume {
        mars_math::vector3<float> min_extent;
        mars_math::vector3<float> max_extent;
    };

    class AABB : public collider_base {
    private:
        collider_volume volume;
    public:

    };
}

#endif