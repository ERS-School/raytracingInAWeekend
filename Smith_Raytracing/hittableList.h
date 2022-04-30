#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

struct HittableList : public Hittable
{
	// - Members - //
	std::vector<shared_ptr<Hittable>> objects;

	// - Constructors - //
	HittableList() {}
	HittableList(const shared_ptr<Hittable>& _object) { Add(_object); }

	// - Methods - //
	void Clear() { objects.clear(); }
	void Add(const shared_ptr<Hittable>& _object) { objects.push_back(_object); }
	virtual bool Hit(const Ray& _r, float _tMin, float _tMax, HitInfo& _rec) const override;
};

#endif
