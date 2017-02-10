#include "TBall.h"

TBall::TBall() : TBall(3, TVector(0, 0, 0), TVector(0, 0, 0)){}

TBall::TBall(const double radius, const TVector& position, const TVector& velocity) : _radius(radius), _position(position), _velocity(velocity){}

TBall::~TBall(){}

void TBall::SetPosition(const TVector& position) {
	_position = position;
}

bool TBall::InGround(const TGround& g) const {
	return (_position.Magnitude() + _radius) < g.GetRadius();
}

void TBall::Draw(){
	glPushMatrix();
	glTranslated(_position.X(), _radius, _position.Z());
	glutSolidSphere(_radius, 20, 20);
	glPopMatrix();
}

void TBall::CalculateVelocity(const TVector& velocity, const double seconds){
	TVector new_velocity = velocity;
	double magnitude = velocity.Magnitude();
	if (magnitude > 1)
		new_velocity *= round(100.0 / magnitude) / 100.0;
	new_velocity *= seconds;
	_velocity = new_velocity;
}

TVector TBall::CalcDistanceTravelled(const double seconds) const {
	return _velocity * seconds;
}

TVector TBall::CalcPosition(const double seconds) const {
	return _position + CalcDistanceTravelled(seconds);
}

void TBall::Move(const double seconds){
	_position = CalcPosition(seconds);
}
