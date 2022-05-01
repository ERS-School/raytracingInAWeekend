#ifndef VEC3_H
#define VEC3_H

#include "rtweekend.h"

#include <cmath>
#include <iostream>

using std::sqrt;

struct Vec3
{
	// - Members - //
	float e[3];

	// - Constructors - //
	Vec3() : e{ 0, 0, 0 } {}
	Vec3(float _e0, float _e1, float _e2) : e{ _e0, _e1, _e2 } {}

	// - Getters - //
	float X() const { return e[0]; }
	float Y() const { return e[1]; }
	float Z() const { return e[2]; }
	float Length() const { return sqrt(LengthSquared()); }
	float LengthSquared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }

	// - Methods - //
	/**
	 * \brief get a Vec3 with xyz values in [0, 1)
	 */
	inline static Vec3 Random() {
		return { RandomFloat(), RandomFloat(), RandomFloat() };
	}
	/**
	 * \brief returns a Vec3 with xyz values in [min, max)
	 * \param _min min value, inclusive
	 * \param _max max value, exclusive
	 */
	inline static Vec3 Random(float _min, float _max) {
		return { RandomFloat(_min, _max), RandomFloat(_min, _max), RandomFloat(_min, _max) };
	}

	// - Overloads - //
	Vec3 operator-() const { return {-e[0], -e[1], -e[2]}; } // overload negation operator
	float operator[](int i) const { return e[i]; }	// allow access of elements of e using array notation on vec3 types
	float& operator[](int i) { return e[i]; }		// allow access to const vec3 types as well (more here https://stackoverflow.com/questions/37043078/c-overloading-array-operator)
	Vec3& operator +=(const Vec3& _v) {
		e[0] += _v.e[0];
		e[1] += _v.e[1];
		e[2] += _v.e[2];
		return *this;
	}
	Vec3& operator*=(const float _t) {
		e[0] *= _t;
		e[1] *= _t;
		e[2] *= _t;
		return *this;
	}
	Vec3& operator/=(const float _t) {
		return *this *= 1 / _t; // math!
	}

};

#pragma region Global Vec3 Utility Functions
				// These go out here so that they're global functions and to avoid having to make them friends of the class
						// (otherwise it tries to overload the bitwise versions? for some reason)
						// https://stackoverflow.com/questions/35943537/error-c2804-binary-operator-has-too-many-parameters-compiling-with-vc-120
						// https://stackoverflow.com/questions/15777944/overloading-the-operator-error-c2804-binary-operator-has-too-many-param

inline std::ostream& operator<<(std::ostream& _out, const Vec3& _v) {
	return _out << _v.e[0] << ' ' << _v.e[1] << ' ' << _v.e[2];
}
inline Vec3 operator+(const Vec3& _u, const Vec3& _v) {
	return { _u.e[0] + _v.e[0], _u.e[1] + _v.e[1], _u.e[2] + _v.e[2] };
}
inline Vec3 operator-(const Vec3& _u, const Vec3& _v) {
	return { _u.e[0] - _v.e[0], _u.e[1] - _v.e[1], _u.e[2] - _v.e[2] };
}
inline Vec3 operator*(const Vec3& _u, const Vec3& _v) {
	return { _u.e[0] * _v.e[0], _u.e[1] * _v.e[1], _u.e[2] * _v.e[2] };
}
inline Vec3 operator*(float _t, const Vec3& _v) {
	return { _t * _v.e[0], _t * _v.e[1], _t * _v.e[2] };
}
inline Vec3 operator*(const Vec3& _v, float _t) {
	return _t * _v;
}
inline Vec3 operator/(Vec3 _v, float _t) {
	return (1 / _t) * _v;
}
inline float Dot(const Vec3& _u, const Vec3& _v) {
	return _u.e[0] * _v.e[0]
		+ _u.e[1] * _v.e[1]
		+ _u.e[2] * _v.e[2];
}
inline Vec3 Cross(const Vec3& _u, const Vec3& _v) {
	return {
		_u.e[1] * _v.e[2] - _u.e[2] * _v.e[1],
		_u.e[2] * _v.e[0] - _u.e[0] * _v.e[2],
		_u.e[0] * _v.e[1] - _u.e[1] * _v.e[0]
	};
}
inline Vec3 UnitVector(Vec3 _v) {
	return _v / _v.Length();
}

inline Vec3 RandomInUnitSphere() {
	while (true)
	{
		auto p = Vec3::Random(-1, 1);
		if (p.LengthSquared() >= 1) continue;
		return p;
	}
}
#pragma endregion

// Type aliases for vec3
using point3 = Vec3;	// 3D point (a vec3)
using colorRGB = Vec3;	// RGB color (a vec3)

#endif