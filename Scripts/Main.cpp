#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	bool success = game.InitSDL();
	if (success)
	{
		game.GameLoop();	//�Q�[�����[�v�J�n
	}
	game.Shutdown();
	return 0;
}