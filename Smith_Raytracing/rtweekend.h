#ifndef RTWEEKEND_H
#define RTWEEKEND_H


#include <cmath>
#include <limits>
#include <memory>

// - Using - //
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// - Constants - //
const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// - Utility Functions - //
inline double DegToRad(const double _degrees) {
	return _degrees * pi / 180.0;
}

// - Common Headers - //
#include "ray.h"
#include "vec3.h"

#endif
