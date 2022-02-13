#include "Game.h"

int main(int argc, char *argv[])
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();	//ゲームループ開始
	}
	game.Shutdown();
	return 0;
}