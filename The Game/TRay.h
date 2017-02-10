#pragma once
#include "TVector.h"
#include <cmath>

class TRay{
public:
	TVector _p, _dir;

	TRay();

	TRay(const double px, const double py, const double pz, const double dirx, const double diry, const double dirz);

	TRay(const TVector& p, const TVector& dir);

	~TRay();

	// returns the distance between two parallel lines, -1 if they are not parallel
	double Distance(const TRay& r) const;

	// returns the perpendicular distance to a point
	double Distance(const TVector& p) const;

	// Intersect two rayz in XZ plane, return the intersection point
	TVector IntersectionXZ(const TRay& r) const;

	// Intersect ray with a circle, return first intersection point
	TVector IntersectCircle(const TVector& center, const double radius) const;
};

