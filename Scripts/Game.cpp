#include "Game.h"
#include "SDL_image.h"
#include <math.h>
#include <stdio.h>

const int WALL_BREADTH = 20;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int PADDLE_WIDTH = 150;
const int PADDLE_HEIGHT = 20;
const int BLOCK_WIDTH = 10;
const int BLOCK_HEIGHT = 3;
const int BALL_SIZE = 15;

Game::Game()
	:mWindow(nullptr)	//初期化子リスト（const変数の初期化）
	,mRenderer(nullptr)
	,mIsRunning(true)
	,mTicksCount(0)
{

}

bool Game::Initialize()	//初期化～生成
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Double-block-breaking", 100, 100, 1000, 800, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create mRenderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	mPaddlePos[0].x = mPaddlePos[1].x = (WINDOW_WIDTH / 2.0f) - (PADDLE_WIDTH / 2.0f);
	mPaddlePos[0].y = WINDOW_HEIGHT - PADDLE_HEIGHT * 2;
	mPaddlePos[1].y = 30.0f;
	mBallPos.x = 1000.0f / 2.0f;
	mBallPos.y = 800.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	return true;
}

//ゲームループ
void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
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
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	
	//終了キーを押したときの処理
	const Uint8* state = SDL_GetKeyboardState(NULL);	//キーボード全体の状態を格納した配列へのポインタを返す
	if (state[SDL_SCANCODE_ESCAPE])
	{
		//ESCキーで終了
		mIsRunning = false;
	}

	//パドルの位置をキー入力で制御する
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_LEFT])
	{
		mPaddleDir = -1;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		mPaddleDir = 1;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	//パドルの処理
	if (mPaddleDir != 0)
	{
		mPaddlePos[0].x += mPaddleDir * 20.0f;
		mPaddlePos[1].x -= mPaddleDir * 20.0f;
		//パドルを画面外に出さないようにする
		//HACK:パドルの数が変わっても対応できるような書き方に修正する。
		if (mPaddlePos[0].x < WALL_BREADTH)
		{
			mPaddlePos[0].x = WALL_BREADTH;
		}
		if (mPaddlePos[1].x < WALL_BREADTH)
		{
			mPaddlePos[1].x = WALL_BREADTH;
		}
		if (mPaddlePos[0].x > WINDOW_WIDTH - PADDLE_WIDTH - WALL_BREADTH)
		{
			mPaddlePos[0].x = WINDOW_WIDTH - PADDLE_WIDTH - WALL_BREADTH;
		}
		if (mPaddlePos[1].x > WINDOW_WIDTH - PADDLE_WIDTH - WALL_BREADTH)
		{
			mPaddlePos[1].x = WINDOW_WIDTH - PADDLE_WIDTH - WALL_BREADTH;
		}
	}

	//ボールの処理
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;
	

	a = atan2(mBallPos.y, mBallPos.x);
	//壁とボールの当たり判定
	if (mBallPos.x < WALL_BREADTH || mBallPos.x > WINDOW_WIDTH - WALL_BREADTH - BALL_SIZE) 
	{
		mBallVel.x *= -1.0f;
	}

	//上のパドルとボールの当たり判定
	//FIXME: ボールがパドルより上に行ったときに、パドルを合わせると当たり判定されてしまうのを修正
	if (mBallPos.y < mPaddlePos[1].y + PADDLE_HEIGHT && mBallPos.y + BALL_SIZE > mPaddlePos[1].y)
	{
		if (mBallPos.x > mPaddlePos[1].x && mBallPos.x < mPaddlePos[1].x + PADDLE_WIDTH)
		{
			mBallVel.y *= -1.0f;
		}
	}

	//下のパドルとボールの当たり判定
	//FIXME: ボールがパドルより下に行ったときに、パドルを合わせると当たり判定されてしまうのを修正
	if (mBallPos.y + BALL_SIZE > mPaddlePos[0].y)
	{
		mBallVel.y *= -1.0f;
	}
	/*
	if (mBallPos.x > mPaddlePos[0].x && mBallPos.x < mPaddlePos[0].x + PADDLE_WIDTH - BALL_SIZE)
	{
		if (mBallPos.y + BALL_SIZE > mPaddlePos[0].y && mBallPos.y < mPaddlePos[0].y + PADDLE_HEIGHT)
		{
			mBallVel.y *= -1.0f;
		}
	}
	*/

	//ボールが画面の外に出たら、ゲーム終了
	if (mBallPos.y + BALL_SIZE < 0 || mBallPos.y > WINDOW_HEIGHT + BALL_SIZE)
	{
		mIsRunning = false;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);	//バッファクリア色
	SDL_RenderClear(mRenderer);	//バッファクリア色でバッファをクリア
	
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);	//壁を描画

	//画面左の壁
	SDL_Rect wall{ 0, 0, WALL_BREADTH, WINDOW_HEIGHT };
	SDL_RenderFillRect(mRenderer, &wall);

	//画面右の壁
	wall.x = WINDOW_WIDTH - WALL_BREADTH;
	wall.y = 0;
	wall.w = WALL_BREADTH;
	wall.h = WINDOW_HEIGHT;
	SDL_RenderFillRect(mRenderer, &wall);


	//パドルを描画
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_Rect paddle1{ mPaddlePos[0].x, mPaddlePos[0].y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_Rect paddle2{ mPaddlePos[1].x, mPaddlePos[1].y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_RenderFillRect(mRenderer, &paddle1);
	SDL_RenderFillRect(mRenderer, &paddle2);

	//ボールを描画
	SDL_Rect ball{ mBallPos.x, mBallPos.y, 15.0f, 15.0f };
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer);	//バッファ切り替え（バックバッファの情報をフロントバッファに描画）
}

//ゲーム終了処理
void Game::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}