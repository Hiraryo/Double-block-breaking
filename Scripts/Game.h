#pragma once
#include "SDL.h"

class Game {
public:
	Game();
	bool InitSDL();
	void GameLoop();
	void Shutdown();

private:
	void ProcessInput();
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool IsGamePlay;
};