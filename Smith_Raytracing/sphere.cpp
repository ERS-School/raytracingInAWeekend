#include "sphere.h"

bool Sphere::Hit(const Ray& _r, float _tMin, float _tMax, HitInfo& _rec) const {
    Vec3 oc = _r.Origin() - Center_;
    auto a = _r.Direction().LengthSquared(); //same as Dot(_r.Direction(), _r.Direction());
    //auto b = 2.0f * Dot(oc, _r.Direction());
    auto halfB = Dot(oc, _r.Direction());
    auto c = oc.LengthSquared() - Radius_ * Radius_; // same as Dot(oc, oc) - _radius * _radius;


	const auto discriminant = halfB * halfB - a * c;
    //auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    const float squrtd = sqrt(discriminant);

    // Find the nearest root that lies within the acceptable range, aka where: _tMin < t < _tMax
    float root = (-halfB - squrtd) / a;
    if (root < _tMin || root > _tMax)
    {
        root = (-halfB + squrtd) / a;
        if (root < _tMin || root > _tMax)
        {
            return false; // didn't hit this sphere
        }
    }

    // Hit! Update the record struct with details about the hit
    _rec.T_ = root;
    _rec.P_ = _r.At(_rec.T_);
    Vec3 outwardNormal = (_rec.P_ - Center_) / Radius_; // unit length normal
    _rec.SetFaceNormal(_r, outwardNormal);
    return true;
}
