#include "TWell.h"


TWell::TWell(){}

TWell::~TWell(){}

TWell::TWell(const int layers, const int bricks_count, const double min_radius, const double max_radius, const double height) {
	bool even;
	int color_scheme = 1;
	for (int i = 0; i < layers; i++) {
		even = true;
		std::vector<TBrick> layer;
		for (int j = 0; j < bricks_count; j++) {
			TBrick brick = TBrick(120 / bricks_count, i * height, height, min_radius, max_radius, colorScheme(color_scheme, even));
			layer.push_back(brick);
			even = !even;
		}
		_bricks.push_back(layer);
		for (int j = 0; j < bricks_count; j++)
			for (int k = j + 1; k < bricks_count; k++)
				_bricks[i][k].MoveRight(360 / bricks_count);
		color_scheme++;
	}
}

void TWell::Draw() const {
	for (const std::vector<TBrick>& v : _bricks)
		for (const TBrick& brick : v)
			if (brick.State())
				brick.Draw();
}

std::pair<int, int> TWell::Collisions(const TBall& ball, const double seconds, int& col) const {
	for (unsigned int i = 0; i < _bricks.size(); i++)
		for (unsigned int j = 0; j < _bricks[i].size(); j++) {
			if (!_bricks[i][j].State())
				continue;
			col = _bricks[i][j].Collisions(ball, seconds);
			if (col > 0)
				return std::make_pair(i, j);
		}
	return std::make_pair(-1, -1);
}

void TWell::Reflections(const TBall& ball, const double seconds, TVector& final_velocity,
	double& collision_time, const int col, std::pair <int, int> index) {
	switch (col) {
	case 1:
	case 2:
		_bricks[index.first][index.second].Faces_Reflection(ball, seconds, final_velocity, collision_time, col == 1);
		break;
	case 3:
	case 4:
		_bricks[index.first][index.second].Sides_Reflection(ball, seconds, final_velocity, collision_time, col == 3);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		_bricks[index.first][index.second].Corners_Reflection(ball, seconds, final_velocity, collision_time, col);
		break;
	}
}

void TWell::DeativateBrick(std::pair <int, int> index) {
	_bricks[index.first][index.second].Deactivate();
	FallBrick(index);
}

bool TWell::State() const {
	for (const std::vector<TBrick>& layer : _bricks)
		for (const TBrick& brick : layer)
			if (brick.State() == true)
				return true;
	return false;
}

void TWell::ReactivateAll() {
	for (std::vector<TBrick>& layer : _bricks)
		for (TBrick& brick : layer)
			brick.Reactivate();
}

void TWell::FallBrick(std::pair<int, int> index) {
	unsigned int layer = index.first + 1;
	while (layer < _bricks.size()) {
		TBrick& brick = _bricks[layer][index.second];
		if (brick.State()) {
			brick.Deactivate();
			_bricks[layer - 1][index.second].SetColor(brick.GetColor());
			_bricks[layer - 1][index.second].Reactivate();
		}
		layer++;
	}
}

void TWell::ResetColors() {
	bool even;
	int color_scheme = 1;
	for (unsigned int i = 0; i < _bricks.size(); i++) {
		even = true;
		for (unsigned int j = 0; j < _bricks[i].size(); j++) {
			_bricks[i][j].SetColor(colorScheme(color_scheme, even));
			even = !even;
		}
		color_scheme++;
	}
}