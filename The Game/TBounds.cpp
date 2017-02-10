#include "TBounds.h"
#include <iostream>

bool TBounds::Wall_Reflection(const TBall& ball, const TGround& ground, const double seconds, TVector& final_velocity, double& collision_time)
{
	TVector next_ball_position = ball.CalcPosition(seconds);
	if (next_ball_position.Magnitude() + ball.GetRadius() < ground.GetRadius())
		return false;
	double absBallVelocity = ball.GetVelocity().Magnitude();
	// Calculate the Ri*V to calculate the collision time
	double RV = ball.GetPosition().Dot(ball.GetVelocity()) / absBallVelocity;
	// Absolute RV
	double abs_RV = abs(RV);
	// Define the initial distance = 60 - 3 = 57
	double initial_distance = ground.GetRadius() - ball.GetRadius();
	// Calculate the determinant
	double Determinant = ((RV*RV) - ball.GetPosition().Dot(ball.GetPosition()) + initial_distance*initial_distance);

	// Calculate the collision time
	collision_time = abs(-abs_RV + sqrt(Determinant)) / absBallVelocity; //distance to collision divided by mag. of velocity

	// Calculate the collision position (normal vector) from: R = r + v*t
	TVector collision_position = ball.CalcPosition(collision_time);
	// Make the collision vector (normal vector) a unit vector
	TVector normal = collision_position.Unit();
	
	// Calculate the velocity of the ball after collision with the invisible wall
	final_velocity = ball.GetVelocity() - normal*(ball.GetVelocity().Dot(normal))*2.0;
	return true;
}