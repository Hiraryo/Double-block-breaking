#pragma once
#include "SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Game {
public:
	Game();
	bool Initialize();
	bool HitCheck();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;

	int mPaddleDir;
	double a;
	Vector2 mPaddlePos[2];
	Vector2 mBallPos;
	Vector2 mBallVel;
	bool ball_f;
};