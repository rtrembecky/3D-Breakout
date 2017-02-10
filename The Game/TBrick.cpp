#include "TBrick.h"

TBrick::TBrick(){}

TBrick::~TBrick(){}

TBrick::TBrick(const double rotation_angle, const double altitude, const double height,
	const double min_radius, const double max_radius, const float color[4])
	: TBat(rotation_angle, altitude, height, min_radius, max_radius, color), state(true){}

bool TBrick::State() const {
	return state;
}

void TBrick::Deactivate() {
	state = false;
}

void TBrick::Reactivate() {
	state = true;
}