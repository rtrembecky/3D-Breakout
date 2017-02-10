#include "TBat.h"

TBat::TBat(){}

TBat::~TBat(){}

TBat::TBat(const double rotation_angle, const double altitude, const double height,
	const double min_radius, const double max_radius, const float color[4])
	: _radius1(min_radius), _radius2(max_radius), _height(height) {
	for (int i = 0; i < 4; i++)
		_color[i] = color[i];
	_lastRight = true;

	// Define a vector for the construction of the ground points of the bats
	TVector initial_vector = TVector(1.0, 0.0, 0.0);

	// Altitude vector
	TVector altitude_vector = TVector(0, altitude, 0);
	
	// Define a vector for the construction of the upper points of the bats
	TVector up_vector = TVector(0.0, height, 0.0);

	// Define the rotation axis
	TVector rotation_axis(0.0, 1.0, 0.0);
	
	// Define the three rotation matrices for the bats
	TMatrix bat_construction = TMatrix(rotation_axis, rotation_angle);

	// Define the rotation matrix for the constuction of the bats
	TMatrix bat_rotation = TMatrix(rotation_axis, rotation_angle);

	// Construct the 16 points of the bats
	_points[0] = initial_vector*min_radius + altitude_vector;
	_points[1] = bat_rotation*_points[0];
	_points[2] = bat_rotation*_points[1];
	_points[3] = bat_rotation*_points[2];
	_points[7] = initial_vector*max_radius + altitude_vector;
	_points[6] = bat_rotation*_points[7];
	_points[5] = bat_rotation*_points[6];
	_points[4] = bat_rotation*_points[5];
	_points[8] = _points[0] + up_vector;
	_points[9] = _points[1] + up_vector;
	_points[10] = _points[2] + up_vector;
	_points[11] = _points[3] + up_vector;
	_points[15] = _points[7] + up_vector;
	_points[14] = _points[6] + up_vector;
	_points[13] = _points[5] + up_vector;
	_points[12] = _points[4] + up_vector;
	CalculateNormals();
	CalculateSides();
}

void TBat::CalculateNormals(){
	_normal[0] = ((_points[8] - _points[0])*(_points[1] - _points[0])).Unit();
	_normal[1] = ((_points[9] - _points[1])*(_points[2] - _points[1])).Unit();
	_normal[2] = ((_points[10] - _points[2])*(_points[3] - _points[2])).Unit();
	_normal[3] = ((_points[11] - _points[3])*(_points[4] - _points[3])).Unit();
	_normal[4] = ((_points[12] - _points[4])*(_points[5] - _points[4])).Unit();
	_normal[5] = ((_points[13] - _points[5])*(_points[6] - _points[5])).Unit();
	_normal[6] = ((_points[14] - _points[6])*(_points[7] - _points[6])).Unit();
	_normal[7] = ((_points[15] - _points[7])*(_points[0] - _points[7])).Unit();
	_normal[8] = ((_points[15] - _points[8])*(_points[9] - _points[8])).Unit();
}

void TBat::CalculateSides(){
	_sideRight = TRay(_points[3], (_points[4] - _points[3]).Unit());
	_sideLeft = TRay(_points[0], (_points[7] - _points[0]).Unit());
}

void TBat::Draw() const {
	glPushAttrib(GL_CURRENT_COLOR);
	glColor3fv(_color);
	//front side
	glBegin(GL_QUAD_STRIP);

	// Front face, first quad
	glNormal3d(_normal[0].X(), _normal[0].Y(), _normal[0].Z());
	glVertex3d(_points[0].X(), _points[0].Y(), _points[0].Z());
	glVertex3d(_points[8].X(), _points[8].Y(), _points[8].Z());

	glVertex3d(_points[1].X(), _points[1].Y(), _points[1].Z());
	glVertex3d(_points[9].X(), _points[9].Y(), _points[9].Z());

	// Front face, second quad
	glNormal3d(_normal[1].X(), _normal[1].Y(), _normal[1].Z());
	glVertex3d(_points[2].X(), _points[2].Y(), _points[2].Z());
	glVertex3d(_points[10].X(), _points[10].Y(), _points[10].Z());

	// Front face, third quad
	glNormal3d(_normal[2].X(), _normal[2].Y(), _normal[2].Z());
	glVertex3d(_points[3].X(), _points[3].Y(), _points[3].Z());
	glVertex3d(_points[11].X(), _points[11].Y(), _points[11].Z());

	//right
	glNormal3d(_normal[3].X(), _normal[3].Y(), _normal[3].Z());
	glVertex3d(_points[4].X(), _points[4].Y(), _points[4].Z());
	glVertex3d(_points[12].X(), _points[12].Y(), _points[12].Z());

	//back side
	glNormal3d(_normal[4].X(), _normal[4].Y(), _normal[4].Z());
	glVertex3d(_points[5].X(), _points[5].Y(), _points[5].Z());
	glVertex3d(_points[13].X(), _points[13].Y(), _points[13].Z());

	glNormal3d(_normal[5].X(), _normal[5].Y(), _normal[5].Z());
	glVertex3d(_points[6].X(), _points[6].Y(), _points[6].Z());
	glVertex3d(_points[14].X(), _points[14].Y(), _points[14].Z());

	glNormal3d(_normal[6].X(), _normal[6].Y(), _normal[6].Z());
	glVertex3d(_points[7].X(), _points[7].Y(), _points[7].Z());
	glVertex3d(_points[15].X(), _points[15].Y(), _points[15].Z());

	//left
	glNormal3d(_normal[7].X(), _normal[7].Y(), _normal[7].Z());
	glVertex3d(_points[0].X(), _points[0].Y(), _points[0].Z());
	glVertex3d(_points[8].X(), _points[8].Y(), _points[8].Z());

	glEnd();

	//top side
	glBegin(GL_QUAD_STRIP);

	//first quad
	glNormal3d(_normal[8].X(), _normal[8].Y(), _normal[8].Z());
	glVertex3d(_points[15].X(), _points[15].Y(), _points[15].Z());
	glVertex3d(_points[8].X(), _points[8].Y(), _points[8].Z());

	glVertex3d(_points[14].X(), _points[14].Y(), _points[14].Z());
	glVertex3d(_points[9].X(), _points[9].Y(), _points[9].Z());

	//second quad
	glVertex3d(_points[13].X(), _points[13].Y(), _points[13].Z());
	glVertex3d(_points[10].X(), _points[10].Y(), _points[10].Z());

	//third quad
	glVertex3d(_points[12].X(), _points[12].Y(), _points[12].Z());
	glVertex3d(_points[11].X(), _points[11].Y(), _points[11].Z());

	glEnd();
	glPopAttrib();
}

void TBat::MoveRight(const double angle){
	TMatrix rotation(TVector(0, 1, 0), angle);
	for (TVector& point : _points) {
		point = rotation * point;
	}
	CalculateNormals();
	CalculateSides();
	_lastRight = true;
}

void TBat::MoveLeft(const double angle){
	TMatrix rotation(TVector(0, 1, 0), -angle);
	for (TVector& point : _points) {
		point = rotation * point;
	}
	CalculateNormals();
	CalculateSides();
	_lastRight = false;
}

int TBat::Collisions(const TBall& ball, const double seconds) const {
	const TVector position = ball.GetPosition();
	const double radius = ball.GetRadius();
	const TVector next_position = ball.CalcPosition(seconds);
	// wrong half-circle 
	if (next_position.Dot((_points[1] + _points[2]) * 0.5) < 0)
		return 0;
	// wrong radius
	if (next_position.Magnitude() + radius < _radius1)
		return 0;
	if (next_position.Magnitude() - radius > _radius2)
		return 0;

	// Face collisions
	if (next_position.Magnitude() >= _radius1 - radius
		&& next_position.Magnitude() <= _radius2 + radius
		&& next_position.Dot(_normal[7]) <= 0
		&& next_position.Dot(_normal[3]) <= 0) {
		if (position.Magnitude() + radius < _radius1)
			return 1;
		if (position.Magnitude() - radius > _radius2)
			return 2;
	}
	// Side collisions
	else if (next_position.Magnitude() >= _radius1
		&& next_position.Magnitude() <= _radius2) {
		if (_sideRight.Distance(next_position) <= radius)
			return 3;
		if (_sideLeft.Distance(next_position) <= radius)
			return 4;
	}
	// Corner collisions
	else {
		if (next_position.Distance(_points[0]) <= radius)
			return 5;
		if (next_position.Distance(_points[3]) <= radius)
			return 6;
		if (next_position.Distance(_points[4]) <= radius)
			return 7;
		if (next_position.Distance(_points[7]) <= radius)
			return 8;
	}
	return 0;
}

int TBat::CollisionsNow(TBall& ball, const double seconds) const {
	const TVector position = ball.GetPosition();
	const double radius = ball.GetRadius();
	// wrong half-circle 
	if (position.Dot(_points[0]) < 0)
		return 0;
	// wrong radius
	if (position.Magnitude() + radius < _radius1)
		return 0;
	if (position.Magnitude() - radius > _radius2)
		return 0;
	
	bool right;
	if (_sideRight.Distance(position) <= radius)
		right = true;
	else if (_sideLeft.Distance(position) <= radius)
		right = false;
	else
		return 0;

	const double dist = radius - (right ? _sideRight : _sideLeft).Distance(position);
	ball.SetPosition(position + _normal[right ? 3 : 7] * dist);

	ball.CalculateVelocity((ball.GetVelocity() + _normal[_lastRight ? 3 : 7] * 0.2).Unit(), seconds);
	return right ? 1 : 2;
}

void TBat::Faces_Reflection(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const bool front) const {
	const double absBallVelocity = ball.GetVelocity().Magnitude();
	// Calculate the Ri*V to calculate the collision time
	const double RV = ball.GetPosition().Dot(ball.GetVelocity()) / absBallVelocity;
	// Absolute RV
	const double abs_RV = abs(RV);
	// Define the initial distance = 60 - 3 = 57
	const double initial_distance = front ? _radius1 - ball.GetRadius() : _radius2 + ball.GetRadius();
	// Calculate the determinant
	const double Determinant = ((RV*RV) - ball.GetPosition().Dot(ball.GetPosition()) + initial_distance*initial_distance);

	// Calculate the collision time - distance to collision divided by mag. of velocity
	collision_time = abs(-abs_RV + sqrt(Determinant)) / absBallVelocity;

	// Calculate the collision position (normal vector) from: R = r + v*t
	const TVector collision_position = ball.GetPosition() + ball.GetVelocity() * collision_time;
	// Make the collision vector (normal vector) unit vector
	const TVector normal = collision_position.Unit();

	// Calculate the velocity of the ball after collision
	const TVector ball_velocity_after_collision = normal * (ball.GetVelocity().Dot(normal));
	final_velocity = ball.GetVelocity() - ball_velocity_after_collision * 2.0;
	
	return;
}

void TBat::Sides_Reflection(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const bool right) const {
	const TRay rayBall(ball.GetPosition(), ball.GetVelocity());
	TRay side;
	TVector normal;
	if (right) {
		normal = _normal[3];
		side = TRay(_points[3] + _normal[3] * ball.GetRadius(), (_points[4] - _points[3]).Unit());
	}
	else {
		normal = _normal[7];
		side = TRay(_points[0] + _normal[7] * ball.GetRadius(), (_points[7] - _points[0]).Unit());
	}
	
	// Calculate the collision position
	const TVector collision_position = rayBall.IntersectionXZ(side);
	
	// Calculate the collision time - distance to collision divided by mag. of velocity
	collision_time = collision_position.Distance(ball.GetPosition()) / ball.GetVelocity().Magnitude();

	// Calculate the velocity of the ball after collision
	const TVector ball_velocity_after_collision = normal * (ball.GetVelocity().Dot(normal));
	final_velocity = ball.GetVelocity() - ball_velocity_after_collision*2.0;
	return;
}

void TBat::Corners_Reflection(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const int corner) const {
	const TRay rayBall(ball.GetPosition(), ball.GetVelocity());
	TVector normal, point;
	const TVector position = ball.GetPosition();
	switch (corner) {
	case 5:
		point = _points[0];
		break;
	case 6:
		point = _points[3];
		break;
	case 7:
		point = _points[4];
		break;
	case 8:
		point = _points[7];
		break;
	}

	// Calculate the collision position
	const TVector collision_position = rayBall.IntersectCircle(point, ball.GetRadius());
	normal = (collision_position - point).Unit();

	// Calculate the collision time - distance to collision divided by mag. of velocity
	collision_time = collision_position.Distance(ball.GetPosition()) / ball.GetVelocity().Magnitude();

	// Calculate the velocity of the ball after collision
	const TVector ball_velocity_after_collision = normal * (ball.GetVelocity().Dot(normal));
	final_velocity = ball.GetVelocity() - ball_velocity_after_collision*2.0;
	return;
}

void TBat::Reflections(const TBall& ball, const double seconds, TVector& final_velocity, double& collision_time, const int col, const bool moving) const {
	switch (col) {
	case 1:
	case 2:
		Faces_Reflection(ball, seconds, final_velocity, collision_time, col == 1);
		break;
	case 3:
	case 4:
		Sides_Reflection(ball, seconds, final_velocity, collision_time, col == 3);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		Corners_Reflection(ball, seconds, final_velocity, collision_time, col);
		break;
	}
	if (moving)
		final_velocity = (final_velocity + _normal[_lastRight ? 3 : 7] * 0.2).Unit();
}

const float* TBat::GetColor() const {
	return _color;
}

void TBat::SetColor(const float* color) {
	for (int i = 0; i < 4; i++)
		_color[i] = color[i];
}