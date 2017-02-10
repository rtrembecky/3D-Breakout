#pragma once
#include "TBat.h"

class TBrick : public TBat
{
	bool state;
public:
	TBrick();
	~TBrick();

	TBrick(const double rotation_angle, const double altitude, const double height,
		const double min_radius, const double max_radius, const float color[4]);

	// true if active, false if hit
	bool State() const;

	void Deactivate();

	void Reactivate();
};

