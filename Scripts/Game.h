#pragma once
#include "SDL.h"
#include "SDL_image.h"

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