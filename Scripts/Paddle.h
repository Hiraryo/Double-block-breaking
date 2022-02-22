#pragma once
#include "SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Paddle {
private:
	Vector2 mPaddlePos[2];
	static const int PADDLE_WIDTH;	//パドルの横幅
	static const int PADDLE_HEIGHT;	//パドルの高さ

public:
	//パドルを動かす
	void Move(int paddleID, double m_speed, const int *mPaddleDir);
};