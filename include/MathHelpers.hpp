#ifndef ASOBIBA_MATHHELPERS_INCLUDED
#define ASOBIBA_MATHHELPERS_INCLUDED

#include <algorithm>

namespace aso {
namespace math {

    template<typename T>
    T clamp(T value, T min, T max) {
        return std::max(std::min(value, max), min);
    }

} // aso::math
} // aso

#endif // ASOBIBA_MATHHELPERS_INCLUDED