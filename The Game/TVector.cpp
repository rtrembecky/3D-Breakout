#include "TVector.h"

TVector::TVector(const double& x, const double& y, const double& z) : _x(x), _y(y), _z(z){}

TVector::TVector() : TVector(0, 0, 0){}

TVector::~TVector(){}

TVector TVector::Unit() const {
	return *this * (1 / Magnitude());
}

double TVector::Magnitude() const {
	return sqrt(Dot(*this));
}

TVector TVector::Invert() const {
	return TVector(-_x, -_y, -_z);
}

TVector TVector::Add(const TVector& v) const {
	return TVector(_x + v._x, _y + v._y, _z + v._z);
}

TVector TVector::Subtract(const TVector& v) const {
	return TVector(_x - v._x, _y - v._y, _z - v._z);
}

TVector TVector::Multiply(const TVector& v) const {
	return TVector(_x * v._x, _y * v._y, _z * v._z);
}

TVector TVector::Multiply(const double& d) const {
	return Multiply(TVector(d, d, d));
}

TVector TVector::operator+(const TVector& v) const {
	return Add(v);
}

TVector TVector::operator-(const TVector& v) const {
	return Subtract(v);
}

TVector TVector::operator*(const double& d) const {
	return Multiply(d);
}

TVector TVector::operator*=(const double& d) {
	*this = *this * d;
	return *this;
}

double TVector::Angle(const TVector& v) const {
	return acos(Unit().Dot(v.Unit()));
}

double TVector::Angle() const {
	return Angle(TVector(1, 0, 0));
}

double TVector::Dot(const TVector& v) const {
	return _x * v._x + _y * v._y + _z * v._z;
}

TVector TVector::Cross(const TVector& v) const {
	return TVector(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x);
}

TVector TVector::operator*(const TVector& v) const {
	return Cross(v);
}

std::ostream& operator<<(std::ostream& os, const TVector& v) {
	os << "(" << v.X() << "," << v.Y() << "," << v.Z() << ")";
	return os;
}

double TVector::Distance(const TVector& v) const {
	return (*this - v).Magnitude();
}