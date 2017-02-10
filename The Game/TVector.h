#pragma once
#include <cmath>
#include <iostream>

class TVector{
	double _x, _y, _z;
public:
	TVector(const double& x, const double& y, const double& z);

	TVector();

	~TVector();

	double X() const { return _x; }

	double Y() const { return _y; }

	double Z() const { return _z; }

	TVector Unit() const;

	double Magnitude() const;

	TVector Invert() const;

	TVector Add(const TVector& v) const;

	TVector Subtract(const TVector& v) const;

	TVector Multiply(const TVector& v) const;
	
	TVector Multiply(const double& d) const;

	TVector operator+(const TVector& v) const;

	TVector operator-(const TVector& v) const;

	TVector operator*(const double& d) const;

	TVector operator*=(const double& d);

	double Angle(const TVector& v) const;

	double Angle() const;

	double Dot(const TVector& v) const;

	TVector Cross(const TVector& v) const;

	TVector operator*(const TVector& v) const;

	// distance between two positions
	double Distance(const TVector& v) const;
};

std::ostream& operator<<(std::ostream& os, const TVector& v);