#pragma once
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Vector2
{
	float x;
	float y;
};

class GameManager {
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	int mPadlleDir;	//パドルの移動方向
	int mBallZanki;	//ボール残機の初期値(この場合の残機数は３つ)
	int mScore;	//スコア
	int mBlockNo;	//ブロックの段数(6x6)
	int mBlockNum;	//ブロックの数
	int mStageNo;
	int i, j;
	float mPaddleMoveSpeed;
	//vector<int> mBlockPosX(6);
	//vector<int> mBlockPosY(6);
	Vector2 mPaddlePos[2];
	Vector2 mBallPos;
	Vector2 mBallVel;
	static const int PADDLE_WIDTH;	//パドルの横幅
	static const int PADDLE_HEIGHT;	//パドルの高さ
	static const int WINDOW_WIDTH;	//ウィンドウの幅
	static const int WINDOW_HEIGHT;	//ウィンドウの高さ
	static const int WALL_BREADTH;	//壁の厚み
	static const int BLOCK_WIDTH;	//ブロックの幅
	static const int BLOCK_HEIGHT;	//ブロックの高さ
	static const int BLOCK_X_START;	//ブロックのX座標(１番左上のブロック)
	static const int BLOCK_Y_START;	//ブロックのY座標(１番左上のブロック)
	static const int BALL_SIZE;		//ボールの大きさ
	static const int SPACE;			//パドルより下のスペースの大きさ
	static const int GAME_WIDTH;	//ゲーム画面の幅

public:
	GameManager();
	bool Initialize();
	//void StageCreate();
	void GameStart();
	void GameEnd();
	void SceneChanger();
	void GameClear();
	void GameOver();
	void Input();
	void Update();
	void Draw();
	bool getIsRunning();	//進行状態を返す関数
	void setIsRunning(bool mIsRunning);	//進行状態を設定する関数
};