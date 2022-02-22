#include "PlayerInput.h"
#include "GameManager.h"
#include "Paddle.h"

void PlayerInput::Input() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			GameManager gameManager;
			gameManager.setIsRunning(false);
		}
	}

	//終了キーを押したときの処理
	const Uint8* state = SDL_GetKeyboardState(NULL);	//キーボード全体の状態を格納した配列へのポインタを返す
	if (state[SDL_SCANCODE_ESCAPE])
	{
		//ESCキーで終了
		GameManager gameManager;
		gameManager.setIsRunning(false);
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		Paddle paddle;
		paddle.Move(10.0f, -1);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{

	}
}