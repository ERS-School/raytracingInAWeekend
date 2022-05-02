#ifndef CAMERA_H
#define CAMERA_H


#include "rtweekend.h"

class Camera
{
private:
	point3 origin_;
	point3 lowerLeftCorner_;
	Vec3 horizontalAxis_;
	Vec3 verticalAxis_;

public:
	Camera(point3 _lookFrom, point3 _lookAt, Vec3 _up, float _fovDegrees, float _aspectRatio)
		: origin_(_lookFrom)
	{
		const auto theta = DegToRad(_fovDegrees);
		const auto h = tan(theta / 2);
		auto viewportHeight = 2.0 * h;
		auto viewportWidth = _aspectRatio * viewportHeight;

		auto w = UnitVector(_lookFrom - _lookAt);
		auto u = UnitVector(Cross(_up, w));
		auto v = Cross(w, u);


		horizontalAxis_ = viewportWidth * u;
		verticalAxis_ = viewportHeight * v;
		lowerLeftCorner_ = origin_ - horizontalAxis_/2 - verticalAxis_/2 - w;
	}

	Ray GetRay(double _s, double _t) const {
		return { origin_, lowerLeftCorner_ + _s * horizontalAxis_ + _t * verticalAxis_ - origin_ };
	}
};


#endif
