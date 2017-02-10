#pragma once
#define _USE_MATH_DEFINES

#include "TVector.h"
#include <cmath>
#include <array>
#include <iterator>

class TMatrix {

	std::array<std::array<double, 3>, 3> _m;

public:
	TMatrix();

	TMatrix(const double a1, const double a2, const double a3,
		const double b1, const double b2, const double b3,
		const double c1, const double c2, const double c3);

	TMatrix(const double phi, const double theta, const double psi);

	TMatrix(const TVector& axis, const double psi);

	~TMatrix();

	TMatrix Add(const TMatrix& m) const;

	TMatrix Subtract(const TMatrix& m) const;

	TMatrix Multiply(const TMatrix& m) const;

	TVector Multiply(const TVector& v) const;

	TMatrix Multiply(const double d) const;

	TMatrix operator*(const TMatrix& m) const;

	TVector operator*(const TVector& v) const;

	TMatrix operator*(const double d) const;

	TMatrix Transpose() const;

	double Det() const;

	double DetMinor(const int x, const int y) const;

	TMatrix Inverse() const;
};