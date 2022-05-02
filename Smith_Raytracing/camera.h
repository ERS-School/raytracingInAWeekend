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
	Vec3 u_; // local right
	Vec3 v_; // local up
	Vec3 w_; // local forward
	float lensRadius_;

public:
	Camera(
		point3 _lookFrom,
		point3 _lookAt,
		Vec3 _up,
		float _fovDegrees, // vertical FOV in degrees
		float _aspectRatio,
		float _aperture,
		float _focusDist)
		:
		origin_(_lookFrom),
		lensRadius_(_aperture / 2.0f)
	{
		const auto theta = DegToRad(_fovDegrees);
		const auto h = tan(theta / 2.0f);
		auto viewportHeight = 2.0f * h;
		auto viewportWidth = _aspectRatio * viewportHeight;

		w_ = UnitVector(_lookFrom - _lookAt);
		u_ = UnitVector(Cross(_up, w_));
		v_ = Cross(w_, u_);

		horizontalAxis_ = _focusDist * static_cast<float>(viewportWidth) * u_;
		verticalAxis_ = _focusDist * static_cast<float>(viewportHeight) * v_;
		lowerLeftCorner_ = origin_ - horizontalAxis_ / 2.0f - verticalAxis_ / 2.0f - _focusDist * w_;
	}

	Ray GetRay(float _s, float _t) const {
		Vec3 rd = lensRadius_ * RandomInUnitDisk();
		Vec3 offset = u_ * rd.X() + v_ * rd.Y();

		return { origin_ + offset, lowerLeftCorner_ + _s * horizontalAxis_ + _t * verticalAxis_ - origin_ - offset };
	}
};


#endif
