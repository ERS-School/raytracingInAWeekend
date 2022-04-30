#include  "hittableList.h"

bool HittableList::Hit(const Ray& _r, float _tMin, float _tMax, HitInfo& _rec) const
{
	HitInfo tempInfo;
	bool hitAnything = false;
	auto closestSoFar = _tMax;

	for (const auto& object:objects) // TODO: if this list is sorted, you could break out of it once you hit something
	{
		if (object->Hit(_r, _tMin, closestSoFar, tempInfo))
		{
			hitAnything = true;
			closestSoFar = tempInfo.T_;
			_rec = tempInfo;
		}
	}

	return hitAnything;
}