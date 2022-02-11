#include "Game.h"
#include "SDL_image.h"

Game::Game()
	:window(nullptr)	//初期化子リスト（const変数の初期化）
	,renderer(nullptr)
	,IsGamePlay(true)
{

}

bool Game::InitSDL()	//初期化～生成
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

//ゲームループ
void Game::GameLoop()
{
	while (IsGamePlay)
	{
		ProcessInput();
	}
}

//キー入力
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDLK_RIGHT:
			//右矢印
			break;

		case SDLK_LEFT:
			//左矢印
			break;


		case SDL_QUIT:
			IsGamePlay = false;
			break;
		}
	}
}

//ゲーム終了処理
void Game::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}