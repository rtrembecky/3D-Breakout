#pragma once
#define _USE_MATH_DEFINES

#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "TVector.h"

#include <cmath>

class TGround {
	TVector _points[37]; // points in the surface of the ground

	TVector _tex_coords[37]; // texture coordinates for points

	TVector _normal; // normal of the ground

	double _radius;
public:
	TGround(const double& radius);

	~TGround();

	double GetRadius() const { return _radius; }

	void Draw();
};