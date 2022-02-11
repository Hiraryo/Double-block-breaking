#include "Game.h"
#include "SDL_image.h"

Game::Game()
	:window(nullptr)	//�������q���X�g�iconst�ϐ��̏������j
	,renderer(nullptr)
	,IsGamePlay(true)
{

}

bool Game::InitSDL()	//�������`����
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Double-block-breaking", 100, 100, 1000, 800, 0);
	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	return true;
}

//�Q�[�����[�v
void Game::GameLoop()
{
	while (IsGamePlay)
	{
		ProcessInput();
	}
}

//�L�[����
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDLK_RIGHT:
			//�E���
			break;

		case SDLK_LEFT:
			//�����
			break;


		case SDL_QUIT:
			IsGamePlay = false;
			break;
		}
	}
}

//�Q�[���I������
void Game::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}