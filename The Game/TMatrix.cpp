#include "TMatrix.h"

TMatrix::TMatrix() : TMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1) {}

TMatrix::TMatrix(const double a1, const double a2, const double a3,
	const double b1, const double b2, const double b3,
	const double c1, const double c2, const double c3) : _m({ { { { a1, a2, a3 } }, { { b1, b2, b3 } }, { { c1, c2, c3 } } } }){}

TMatrix::TMatrix(const double phi, const double theta, const double psi){
	double rad_phi = (M_PI*phi) / 180.0;
	double rad_theta = (M_PI*theta) / 180.0;
	double rad_psi = (M_PI*psi) / 180.0;
	double cos_phi = cos(rad_phi);
	double cos_theta = cos(rad_theta);
	double cos_psi = cos(rad_psi);
	double sin_phi = sin(rad_phi);
	double sin_theta = sin(rad_theta);
	double sin_psi = sin(rad_psi);
	TMatrix result =
		TMatrix(1, 0, 0, 0, cos_phi, -sin_phi, 0, sin_phi, cos_phi)
		* TMatrix(cos_theta, 0, sin_theta, 0, 1, 0, -sin_theta, 0, cos_theta)
		* TMatrix(cos_psi, -sin_psi, 0, sin_psi, cos_psi, 0, 0, 0, 1);
	_m = result._m;
}

TMatrix::TMatrix(const TVector& axis, const double psi){
	TVector v = axis.Unit();
	double rad_psi = (M_PI*psi) / 180.0;
	double c = cos(rad_psi);
	double s = sin(rad_psi);
	double t = 1 - c;

	_m[0][0] = c + v.X()*v.X()*t;
	_m[1][1] = c + v.Y()*v.Y()*t;
	_m[2][2] = c + v.Z()*v.Z()*t;

	double tmp1 = v.X()*v.Y()*t;
	double tmp2 = v.Z()*s;
	_m[1][0] = tmp1 + tmp2;
	_m[0][1] = tmp1 - tmp2;
	tmp1 = v.X()*v.Z()*t;
	tmp2 = v.Y()*s;
	_m[2][0] = tmp1 - tmp2;
	_m[0][2] = tmp1 + tmp2;
	tmp1 = v.Y()*v.Z()*t;
	tmp2 = v.X()*s;
	_m[2][1] = tmp1 + tmp2;
	_m[1][2] = tmp1 - tmp2;
}

TMatrix::~TMatrix(){}

TMatrix TMatrix::Add(const TMatrix& m) const {
	return TMatrix(
		_m[0][0] + m._m[0][0],
		_m[0][1] + m._m[0][1],
		_m[0][2] + m._m[0][2],
		_m[1][0] + m._m[1][0],
		_m[1][1] + m._m[1][1],
		_m[1][2] + m._m[1][2],
		_m[2][0] + m._m[2][0],
		_m[2][1] + m._m[2][1],
		_m[2][2] + m._m[2][2]);
}

TMatrix TMatrix::Subtract(const TMatrix& m) const {
	return TMatrix(
		_m[0][0] - m._m[0][0],
		_m[0][1] - m._m[0][1],
		_m[0][2] - m._m[0][2],
		_m[1][0] - m._m[1][0],
		_m[1][1] - m._m[1][1],
		_m[1][2] - m._m[1][2],
		_m[2][0] - m._m[2][0],
		_m[2][1] - m._m[2][1],
		_m[2][2] - m._m[2][2]);
}

TMatrix TMatrix::Multiply(const TMatrix& m) const {
	return TMatrix(
		_m[0][0] * m._m[0][0] + _m[0][1] * m._m[1][0] + _m[0][2] * m._m[2][0],
		_m[0][0] * m._m[0][1] + _m[0][1] * m._m[1][1] + _m[0][2] * m._m[2][1],
		_m[0][0] * m._m[0][2] + _m[0][1] * m._m[1][2] + _m[0][2] * m._m[2][2],
		_m[1][0] * m._m[0][0] + _m[1][1] * m._m[1][0] + _m[1][2] * m._m[2][0],
		_m[1][0] * m._m[0][1] + _m[1][1] * m._m[1][1] + _m[1][2] * m._m[2][1],
		_m[1][0] * m._m[0][2] + _m[1][1] * m._m[1][2] + _m[1][2] * m._m[2][2],
		_m[2][0] * m._m[0][0] + _m[2][1] * m._m[1][0] + _m[2][2] * m._m[2][0],
		_m[2][0] * m._m[0][1] + _m[2][1] * m._m[1][1] + _m[2][2] * m._m[2][1],
		_m[2][0] * m._m[0][2] + _m[2][1] * m._m[1][2] + _m[2][2] * m._m[2][2]);
}

TVector TMatrix::Multiply(const TVector& v) const {
	return TVector(
		_m[0][0] * v.X() + _m[0][1] * v.Y() + _m[0][2] * v.Z(),
		_m[1][0] * v.X() + _m[1][1] * v.Y() + _m[1][2] * v.Z(),
		_m[2][0] * v.X() + _m[2][1] * v.Y() + _m[2][2] * v.Z());
}

TMatrix TMatrix::Multiply(const double d) const {
	return TMatrix(
		_m[0][0] * d, _m[0][1] * d, _m[0][2] * d,
		_m[1][0] * d, _m[1][1] * d, _m[1][2] * d,
		_m[2][0] * d, _m[2][1] * d, _m[2][2] * d);
}

TMatrix TMatrix::operator*(const TMatrix& m) const {
	return Multiply(m);
}

TVector TMatrix::operator*(const TVector& v) const {
	return Multiply(v);
}

TMatrix TMatrix::operator*(const double d) const {
	return Multiply(d);
}

TMatrix TMatrix::Transpose() const {
	return TMatrix(_m[0][0], _m[1][0], _m[2][0], _m[0][1], _m[1][1], _m[2][1], _m[0][2], _m[1][2], _m[2][2]);
}

double TMatrix::Det() const {
	return _m[0][0] * _m[1][1] * _m[2][2] + _m[0][1] * _m[1][2] * _m[2][0] + _m[0][2] * _m[1][0] * _m[2][1]
		 - _m[0][0] * _m[1][2] * _m[2][1] - _m[0][1] * _m[1][0] * _m[2][2] - _m[0][2] * _m[1][1] * _m[2][0];
}

double TMatrix::DetMinor(const int x, const int y) const {
	int x1 = x == 0 ? 1 : 0;
	int x2 = x == 2 ? 1 : 2;
	int y1 = y == 0 ? 1 : 0;
	int y2 = y == 2 ? 1 : 2;
	return _m[x1][y1] * _m[x2][y2] - _m[x1][y2] * _m[x2][y1];
}

TMatrix TMatrix::Inverse() const {
	double d = 1 / Det();
	TMatrix cofactor = TMatrix(DetMinor(0, 0), -DetMinor(1, 0), DetMinor(2, 0), -DetMinor(0, 1), DetMinor(1, 1), -DetMinor(2, 1), DetMinor(0, 2), -DetMinor(1, 2), DetMinor(2, 2));
	return cofactor * d;
}