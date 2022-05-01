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
	Camera() {
		auto aspectRatio = 16.0 / 9.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = aspectRatio * viewportHeight;
		auto focalLength = 1.0;

		origin_ = point3(0, 0, 0);
		horizontalAxis_ = Vec3(viewportWidth, 0.0, 0.0);
		verticalAxis_ = Vec3(0.0, viewportHeight, 0.0);
		lowerLeftCorner_ = origin_ - horizontalAxis_ / 2 - verticalAxis_ / 2 - Vec3(0, 0, focalLength);
	}

	Ray GetRay(double _u, double _v) const {
		return { origin_, lowerLeftCorner_ + _u * horizontalAxis_ + _v * verticalAxis_ - origin_ };
	}
};


#endif
