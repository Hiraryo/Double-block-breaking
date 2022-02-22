#include "Block.h"

//ブロックの横幅
const int Block::BLOCK_WIDTH = 30;

//ブロックの高さ
const int Block::BLOCK_HEIGHT = 10;

Block::Block(float positionX, float positionY) {
	this->positionX = positionX;
	this->positionY = positionY;
	m_blockState = true;
}

void Block::Destroy() {
	m_blockState = false;
	//ボールに当たったブロックを消す
	//AddScore(100);	//点数を加算
}