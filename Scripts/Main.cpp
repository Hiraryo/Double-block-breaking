#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	bool success = game.InitSDL();
	if (success)
	{
		game.GameLoop();	//ゲームループ開始
	}
	game.Shutdown();
	return 0;
}