#include "GameManager.h"

int main(int argc, char *argv[])
{
	GameManager gameManager;
	bool success = gameManager.Initialize();
	if (success)
	{
		gameManager.GameStart();	//ゲーム開始
	}
	gameManager.GameEnd();
	return 0;
}