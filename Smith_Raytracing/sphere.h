#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

struct Sphere : public Hittable
{
	// - Members - //
	point3 Center_;
	float Radius_;

	// - Constructors - //
	Sphere() = default;
	Sphere(point3 _center, float _radius) : Center_(_center), Radius_(_radius) {}

	// - Methods - //
	bool Hit(const Ray& _r, float _tMin, float _tMax, HitInfo& _rec) const override;
};

#endif
