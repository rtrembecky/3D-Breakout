#pragma once
#include "TBrick.h"
#include <vector>

class TWell
{
	std::vector<std::vector<TBrick> > _bricks;

public:
	TWell();
	~TWell();

	TWell(const int layers, const int bricks_count, const double min_radius, const double max_radius, const double height);

	void Draw() const;

	// Checks for collisions on bricks. Returns -1 if collision isn't going to happen, index of colliding brick otherwise.
	std::pair<int, int> Collisions(const TBall& ball, const double seconds, int& col) const;

	// Calculate reflections
	void Reflections(const TBall& ball, const double seconds, TVector& final_velocity,
		double& collision_time, const int col, std::pair <int, int> index);

	// Deactivate a brick.
	void DeativateBrick(std::pair <int, int> index);

	// Return the state of the well - false if all the bricks have been deactivated, true otherwise.
	bool State() const;

	// Activate all the bricks.
	void ReactivateAll();

	// After a brick has been deactivated, check if there is a brick above. If so, make it "fall".
	void FallBrick(std::pair<int, int> index);

	// Reset colors of all the bricks.
	void ResetColors();
};

