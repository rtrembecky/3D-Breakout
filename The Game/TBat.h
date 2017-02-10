#pragma once
#include "TVector.h"
#include "TBall.h"
#include "TMatrix.h"
#include "TRay.h"
#include "Colors.h"

class TBat
{
	bool _lastRight;
protected:
	double _radius1, _radius2, _height;

	TRay _sideLeft, _sideRight;

	float _color[4];
public:
	std::array<TVector, 9> _normal; // normals

	std::array<TVector, 16> _points; // points for the first bat

	// Default constructor
	TBat();

	~TBat();

	TBat(const double rotation_angle, const double altitude, const double height,
		const double min_radius, const double max_radius, const float color[4]);

	// Draws the bats
	void Draw() const; 

	// Recalculates normals based on points
	void CalculateNormals();

	// Recalculates right and left side rays
	void CalculateSides();

	// Moves the bat right
	void MoveRight(const double angle); 

	// Moves the bat left
	void MoveLeft(const double angle);

	// Checks for collision next frame, returns face/side/corner-specific number
	int Collisions(const TBall& ball, const double seconds) const;

	int CollisionsNow(TBall& ball, const double seconds) const;

	// Calculate the reflection off the face
	void Faces_Reflection(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const bool front) const;

	// Calculate the reflection off the side
	void Sides_Reflection(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const bool front) const;

	// Calculate the reflection off the corner
	void Corners_Reflection(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const int corner) const;

	// Calculate the right reflection
	void Reflections(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const int col, const bool moving) const;

	const float* GetColor() const;

	void SetColor(const float color[4]);
};