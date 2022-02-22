#pragma once
#include "SDL.h"

class Ball {
private:
	float m_speed;
	static const float BALL_RADIUS;

public:
	Ball(float moveSpeed);
	void Move();
};