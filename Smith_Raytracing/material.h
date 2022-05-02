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
	 * \param _attenuation what tinge does incoming light get shifted toward?
	 * \param _scattered resulting ray
	 * \return TRUE if the ray is not absorbed
	 */
	virtual bool Scatter(const Ray& _rIn, const HitInfo& _info, colorRGB& _attenuation, Ray& _scattered) const = 0;
};

/**
 * \brief Surfaces that diffuse/scatter light
 */
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

/**
 * \brief Surfaces that reflect light in a range from perfect mirror to very fuzzy
 */
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
		_scattered = Ray(_info.P_, reflected + Fuzziness_ * RandomInUnitSphere()); // slightly offset our ray within a unit Sphere to fuzz (average) the reflection
		_attenuation = Albedo_;
		return (Dot(_scattered.Direction(), _info.Normal_) > 0);
	}
};

/**
 * \brief "Surfaces" that refract and reflect light (both happen at once!) If it can't refract (see Snell's law), then it will reflect
 */
struct Dielectric : public Material
{
	// - Members - //
	float RefractionIndex_;

	// - Constructors - //
	Dielectric(float _refractionIndex) : RefractionIndex_(_refractionIndex) {}

	// - Methods - //
	virtual bool Scatter(const Ray& _rIn, const HitInfo& _info, colorRGB& _attenuation, Ray& _scattered) const override {
		_attenuation = colorRGB(1.0, 1.0, 1.0);
		const float refractionRatio = _info.FrontFace_ ? (1.0f / RefractionIndex_) : RefractionIndex_;

		const Vec3 unitDir = UnitVector(_rIn.Direction());
		const float cosTheta = fmin(Dot(-unitDir, _info.Normal_), 1.0f);
		const float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

		const bool cannotRefract = refractionRatio * sinTheta > 1.0f;
		Vec3 direction;

		if (cannotRefract  || Reflectance(cosTheta, refractionRatio) > RandomFloat())
			direction = Reflect(unitDir, _info.Normal_);
		else
			direction = Refract(unitDir, _info.Normal_, refractionRatio);

		_scattered = Ray(_info.P_, direction);
		return true;
	}
private:
	/**
	 * \brief Schlick's approximation for reflectance
	 * \param _cosine cosine
	 * \param _refIdx reflective index
	 */
	static float Reflectance(float _cosine, float _refIdx) {
		auto r0 = (1.0f - _refIdx) / (1.0f + _refIdx);
		r0 = r0 * r0;
		return r0 + (1.0f - r0) * pow((1.0f - _cosine), 5.0f);
	}
};

#endif
