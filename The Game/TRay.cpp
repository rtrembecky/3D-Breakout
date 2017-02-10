#include "TRay.h"

TRay::TRay(){}

TRay::TRay(const double px, const double py, const double pz, const double dirx, const double diry, const double dirz) : _p(px, py, pz), _dir(dirx, diry, dirz) {}

TRay::TRay(const TVector& p, const TVector& dir) : _p(p), _dir(dir) {}

TRay::~TRay(){}

double TRay::Distance(const TVector& p) const {
	return (_dir.Cross((_p - p))).Magnitude() / _dir.Magnitude();
}

double TRay::Distance(const TRay& r) const {
	double dot = _dir.Dot(r._dir);
	if (dot != 1)
		return -1;
	return Distance(r._p);
}

TVector TRay::IntersectionXZ(const TRay& r) const {
	double dx = r._p.X() - _p.X();
	double dz = r._p.Z() - _p.Z();
	double det = r._dir.X() * _dir.Z() - r._dir.Z() * _dir.X();
	double u = (dz * r._dir.X() - dx * r._dir.Z()) / det;
	return _p + _dir * u;
}

TVector TRay::IntersectCircle(const TVector& center, const double radius) const {
	double t[2];        // collision time
	TVector point[2];   // intersection points

	TVector d = _p - center;
	double a = _dir.Dot(_dir);
	double b = d.Dot(_dir);
	double c = d.Dot(d) - radius * radius;

	double disc = b * b - a * c;
	if (disc < 0.0f) {
		std::cout << "discriminant lower than 0..." << std::endl;
		return TVector();
	}

	double sqrtDisc = sqrt(disc);
	double invA = 1.0f / a;
	t[0] = (-b - sqrt(disc)) * invA;
	//t[1] = (-b + sqrtDisc) * invA;

	//for (int i = 0; i < 2; ++i) {
	int i = 0;
	point[i] = _p + _dir * t[i];
	//}
	return point[0];
}