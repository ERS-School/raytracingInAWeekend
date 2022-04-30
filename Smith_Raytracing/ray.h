#ifndef RAY_H
#define RAY_H


#include "vec3.h"

struct Ray
{
	// - Members - //
	point3 Origin_;
	Vec3 Direction_;

	// - Constructors - //
	Ray() = default;
	Ray(const point3 _origin, const Vec3& _direction)
		: Origin_(_origin), Direction_(_direction) {}

	// - Getters - //
	point3 Origin() const { return Origin_; }
	Vec3 Direction() const { return Direction_; }

	// - Methods - //
	/**
	 * \brief Get a linearly interpolated point along the ray
	 * \param t how far (+/-) along the ray to travel
	 * \return point Vec3 in space
	 */
	point3 At(float t) const {
		return Origin_ + t * Direction_;
	}
};

#endif
