#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "rtweekend.h"

struct HitInfo;

struct Material
{
	/**
	 * \brief Represents how light (rays) interact with a material
	 * \param _rIn incident ray
	 * \param _info info about where/how the incident ray hit the surface
	 * \param _attenuation attenuation
	 * \param _scattered resulting ray
	 * \return TRUE if the ray is not absorbed
	 */
	virtual bool Scatter(const Ray& _rIn, const HitInfo& _info, colorRGB& _attenuation, Ray& _scattered) const = 0;
};

struct Lambertian : public Material
{
	// - Members - //
	colorRGB Albedo_;

	// - Constructor - //
	Lambertian(const colorRGB& _albedo) : Albedo_(_albedo) {}

	virtual bool Scatter(const Ray& _rIn, const HitInfo& _info, colorRGB& _attenuation, Ray& _scattered) const override {
		auto scatterDir = _info.Normal_ + RandomUnitVector();

		// Catch degenerate scatter direction
		if (scatterDir.NearZero())
			scatterDir = _info.Normal_;

		_scattered = Ray(_info.P_, scatterDir);
		_attenuation = Albedo_;
		return true;
	}
	// design choices:
	//	- always scatter, and attenuate by mat's reflectance
	//	- OR scatter sans attenuation, but absorb 1 - reflectance
	//	- OR a mix of those
	//
	//	- only scatter with some probability (P) and have attenuation be 1/P

};

struct Metal : Material
{
	// - Members - //
	colorRGB Albedo_;
	float Fuzziness_;

	// - Constructors - //
	Metal(const colorRGB& _albedo, float _fuzziness) : Albedo_(_albedo), Fuzziness_(_fuzziness < 1 ? _fuzziness : 1) {}

	// - Methods - //
	virtual bool Scatter(const Ray& _rIn, const HitInfo& _info, colorRGB& _attenuation, Ray& _scattered) const override {
		const Vec3 reflected = Reflect(UnitVector(_rIn.Direction()), _info.Normal_);
		_scattered = Ray(_info.P_, reflected + Fuzziness_ * RandomInUnitSphere()); // slightly offset our ray within a unit sphere to fuzz (average) the reflection
		_attenuation = Albedo_;
		return (Dot(_scattered.Direction(), _info.Normal_) > 0);
	}
};
#endif
