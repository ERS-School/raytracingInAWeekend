#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct HitInfo
{
	// - Members - //
	point3 P_;			// point of intersection with surface
	Vec3 Normal_;		// normal of surface at P
	float T_{};			// lerp distance along the ray that got us P
	bool FrontFace_{};	// did we hit the front?

	// - Constructor - //
	HitInfo() = default;

	// - Methods - //
	inline void SetFaceNormal(const Ray& _r, const Vec3& _outwardNormal) {
		FrontFace_ = Dot(_r.Direction(), _outwardNormal) < 0;	// if ray->surface and Normal point in opposite directions, we hit the front of the surface
		Normal_ = FrontFace_ ? _outwardNormal : -_outwardNormal;	
	}
};

struct Hittable
{
	/**
	 * \brief Check if a given ray hits this object
	 * \param _r incoming Ray
	 * \param _tMin lower bounds of valid lerp interval T must be >= this value
	 * \param _tMax upper bounds of valid lerp interval. T must be <= this value
	 * \param _rec details of the intersection
	 * \return Bool has been hit?
	 */
	virtual bool Hit(const Ray& _r, float _tMin, float _tMax, HitInfo& _rec) const = 0;
};

#endif
