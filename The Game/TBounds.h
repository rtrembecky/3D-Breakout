#pragma once
#include "TBall.h"
#include "TGround.h"

class TBounds
{
public:
	TBounds(){};
	~TBounds(){};

	bool Wall_Reflection(const TBall& ball, const TGround& ground, const double seconds, TVector& final_velocity, double& collision_time);
};