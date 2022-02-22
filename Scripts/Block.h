#pragma once
#include "SDL.h"

class Block {
private:
	static const int BLOCK_WIDTH;
	static const int BLOCK_HEIGHT;
	bool m_blockState;
	float positionX, positionY;	//ブロックを描画する初期の座標（左上）

public:
	Block(float positionX, float positionY);
	void Destroy();
};