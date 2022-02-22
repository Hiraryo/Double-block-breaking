#include "Ball.h"

//ボールの半径
const float Ball::BALL_RADIUS = 15.0f;

Ball::Ball(float moveSpeed) {
	this->m_speed = moveSpeed;
}

void Ball::Move() {
	//ボールを動かす。跳ね返らす。
}