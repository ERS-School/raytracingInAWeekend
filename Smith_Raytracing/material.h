#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

struct HitInfo;

struct Material
{
	virtual bool Scatter(const Ray& _rIn, const HitInfo& _info, colorRGB& attenuation, Ray _scattered) const = 0;
};

#endif
