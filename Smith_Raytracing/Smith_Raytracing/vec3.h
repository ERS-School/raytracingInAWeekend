#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
public:
	// - Members - //
	float e[3];

	// - Constructors - //
	vec3() : e{ 0, 0, 0 } {};
	vec3(float e0, float e1, float e2) : e{ e0, e1, e2 } {};

	// - Getters - //
	float X() const { return e[0]; };
	float Y() const { return e[1]; };
	float Z() const { return e[2]; };
	float Length() const { return sqrt(LengthSquared()); }
	float LengthSquared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }

	// - Overloads - //
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }; // overload negation operator
	float operator[](int i) const { return e[i]; }	// allow access of elements of e using array notation on vec3 types
	float& operator[](int i) { return e[i]; };		// allow access to const vec3 types as well (more here https://stackoverflow.com/questions/37043078/c-overloading-array-operator)
	vec3& operator +=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}
	vec3& operator*=(const float t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	vec3& operator/=(const float t) {
		return *this *= 1 / t; // math!
	}
				// overload as friend functions of the class. https://stackoverflow.com/questions/15777944/overloading-the-operator-error-c2804-binary-operator-has-too-many-param
				// (otherwise it's trying to overload the bitwise versions? for some reason) https://stackoverflow.com/questions/35943537/error-c2804-binary-operator-has-too-many-parameters-compiling-with-vc-120
	friend inline std::ostream& operator<<(std::ostream& out, const vec3& v) {	
		return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];					
	}
	friend inline vec3 operator+(const vec3& u, const vec3& v) {
		return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
	}
	friend inline vec3 operator-(const vec3& u, const vec3& v) {
		return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	}
	// TODO: continue writing from section 3.2
};


// Type aliases for vec3
using point3 = vec3;   // 3D point
using colorRGB = vec3;    // RGB color

#endif