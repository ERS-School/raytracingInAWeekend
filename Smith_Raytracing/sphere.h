#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

struct Sphere : public Hittable
{
	// - Members - //
	point3 Center_;
	float Radius_;
	shared_ptr<Material> MaterialPtr_;

	// - Constructors - //
	Sphere() = default;
	Sphere(point3 _center, float _radius, shared_ptr<Material> _mat)
		: Center_(_center), Radius_(_radius), MaterialPtr_(std::move(_mat)) {}

	// - Methods - //
	bool Hit(const Ray& _r, float _tMin, float _tMax, HitInfo& _info) const override;
};

#endif
