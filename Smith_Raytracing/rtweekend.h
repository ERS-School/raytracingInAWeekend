#ifndef RTWEEKEND_H
#define RTWEEKEND_H


#include <cmath>
#include <cstdlib>
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
/**
 * \brief Returns a random real number in [0, 1)
 */
inline double RandomDouble() {
	return rand() / (RAND_MAX + 1.0);
}
/**
 * \brief returns a number in [min, max)
 * \param _min min value, inclusive
 * \param _max max value, exclusive
 */
inline double RandomDouble(double _min, double _max) {
	return _min + (_max - _min) * RandomDouble();
}
inline float Clamp(float _x, float _min, float _max) {
	if (_x < _min) return _min;
	if (_x > _max) return _max;
	return _x;
}
// - Common Headers - //
#include "ray.h"
#include "vec3.h"

#endif
