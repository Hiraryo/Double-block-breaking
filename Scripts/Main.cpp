#include "Game.h"

int main(int argc, char *argv[])
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();	//�Q�[�����[�v�J�n
	}
	game.Shutdown();
	return 0;
}