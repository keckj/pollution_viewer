
#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <algorithm>

namespace Utils {

    template <typename F>
    bool areEqual(const F a, const F b) {
        static_assert(std::is_floating_point<F>::value, "F must be floating point !");
        return (std::abs(a - b) <= 10*std::numeric_limits<F>::epsilon() * std::max(std::abs(a), std::abs(b)));
    }

}


#endif /* end of include guard: UTILS_H */
