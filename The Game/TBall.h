#pragma once
#include "TVector.h"
#include "TGround.h"
#include "GL\freeglut.h"
#include <cmath>

class TBall
{
	double _radius;

	TVector _position;

	TVector _velocity;
public:
	TBall();

	TBall(const double radius, const TVector& position, const TVector& velocity = TVector(0, 0, 0));
	
	~TBall();

	// Getters
	double GetRadius() const { return _radius; };
	
	TVector GetPosition() const { return _position; };

	void SetPosition(const TVector& position);
	
	TVector GetVelocity() const { return _velocity; };

	// Checks whether the ball is in the given ground
	bool InGround(const TGround& g) const;

	// Draws the ball
	void Draw();
	
	// Assigns the ball a velocity
	void CalculateVelocity(const TVector& velocity, const double seconds);
	
	// Calculates the new position
	TVector CalcPosition(const double seconds) const;

	// Calculates the distance traveled
	TVector CalcDistanceTravelled(const double seconds) const;

	// Moves the ball
	void Move(const double seconds);
};