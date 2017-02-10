#include "TGround.h"

TGround::TGround(const double& radius) : _radius(radius) {
	int angle = 0;
	double rad_angle, x, y = 0.0, z, cos, sin;
	for (int i = 0; i <= 36; i++)
	{
		// Transform degrees in rads
		rad_angle = (M_PI*angle) / 180.0;

		angle += 10;

		cos = std::cos(rad_angle);
		sin = std::sin(rad_angle);

		// Calculate the x and z co-ordinates of a circle ground
		x = cos * _radius;
		z = sin * _radius;
		
		_points[i] = TVector(x, y, z);
		_tex_coords[i] = TVector((cos + 1.0)*0.5, (sin + 1.0)*0.5, 0);
	}
	// Construct the vector for the normal of the ground
	_normal = TVector(0.0, 1.0, 0.0);
}

TGround::~TGround(){}

void TGround::Draw(){
	glNormal3d(_normal.X(), _normal.Y(), _normal.Z());

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord3f(0.5, 0.5, 0);
	glVertex3d(0, 0, 0);
	for (int i = 0; i <= 36; i++)
	{
		glTexCoord3d(_tex_coords[i].X(), _tex_coords[i].Y(), _tex_coords[i].Z());
		glVertex3d(_points[i].X(), _points[i].Y(), _points[i].Z());
	}
	glEnd();
}