#include "GameManager.h"

//パドルの横幅
const int GameManager::PADDLE_WIDTH = 180;

//パドルの高さ
const int GameManager::PADDLE_HEIGHT = 20;

//壁の厚み
const int GameManager::WALL_BREADTH = 20;

//ウィンドウの幅
const int GameManager::WINDOW_WIDTH = 1000;

//ウィンドウの高さ
const int GameManager::WINDOW_HEIGHT = 800;

//ブロックの幅
const int GameManager::BLOCK_WIDTH = 120;

//ブロックの高さ
const int GameManager::BLOCK_HEIGHT = 40;

//ブロックのX座標(１番左上のブロック)
const int GameManager::BLOCK_X_START = 130;

//ブロックのY座標(１番左上のブロック)
const int GameManager::BLOCK_Y_START = 150;

//ボールの大きさ
const int GameManager::BALL_SIZE = 15;

//パドルより下のスペースの大きさ
const int GameManager::SPACE = 50;

//ゲーム画面の幅
const int GameManager::GAME_WIDTH = 800;

GameManager::GameManager()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mIsRunning(true)
	,mTicksCount(0)
{
	mPadlleDir = 0;
	mBlockNo = 6;
	mStageNo = 0;
	mBlockNum = 0;
	mScore = 0;
	mBallZanki = 3;
	i = 0;
	j = 0;
	mPaddleMoveSpeed = 20.0f;
	mPaddlePos[0].x = WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2;
	mPaddlePos[0].y = SPACE;
	mPaddlePos[1].x = WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2;
	mPaddlePos[1].y = WINDOW_HEIGHT - PADDLE_HEIGHT - SPACE;
	mBallPos.x = WINDOW_WIDTH / 2;
	mBallPos.y = WINDOW_HEIGHT / 2;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
}

bool GameManager::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Double-block-breaking", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

	return true;
}

void GameManager::GameStart()
{
	//StageCreate();
	while (mIsRunning)
	{
		Input();	//キー入力処理
		Update();	//ゲーム状態更新
		Draw();		//画面更新
	}
}

/*
void GameManager::StageCreate()
{
	for (i = 0; i < mBlockNum; i++)
	{
		mBlockPosX.push_back((i + 1) * BLOCK_X_START);	//末尾にどんどん追加
	}
	for (i = 0; i < mBlockNum; i++)
	{
		mBlockPosY.push_back((i + 1) * BLOCK_Y_START - (100 * i));
	}
}
*/

void GameManager::Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
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
	mPadlleDir = 0;
	if (state[SDL_SCANCODE_LEFT])
	{
		mPadlleDir = -1;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		mPadlleDir = 1;
	}
}

void GameManager::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	if (mPadlleDir != 0)
	{
		mPaddlePos[0].x -= mPadlleDir * mPaddleMoveSpeed;
		mPaddlePos[1].x += mPadlleDir * mPaddleMoveSpeed;

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

	//壁とボールの当たり判定
	if (mBallPos.x < WALL_BREADTH || mBallPos.x > WINDOW_WIDTH - WALL_BREADTH - BALL_SIZE)
	{
		mBallVel.x *= -1.0f;
	}

	//上のパドルとボールの当たり判定
	//FIXME: ボールがパドルより上に行ったときに、パドルを合わせると当たり判定されてしまうのを修正
	if ((mPaddlePos[0].x + PADDLE_WIDTH > mBallPos.x) && (mPaddlePos[0].x < mBallPos.x + BALL_SIZE) && (mPaddlePos[0].y < mBallPos.y + BALL_SIZE) && (mPaddlePos[0].y + PADDLE_HEIGHT > mBallPos.y) && mBallPos.y > SPACE) {
		mBallVel.y *= -1.0f;
	}

	//下のパドルとボールの当たり判定
	//FIXME: ボールがパドルより下に行ったときに、パドルを合わせると当たり判定されてしまうのを修正
	if ((mPaddlePos[1].x + PADDLE_WIDTH > mBallPos.x) && (mPaddlePos[1].x < mBallPos.x + BALL_SIZE) && (mPaddlePos[1].y < mBallPos.y + BALL_SIZE) && (mPaddlePos[1].y + PADDLE_HEIGHT > mBallPos.y)) {
		mBallVel.y *= -1.0f;
	}

	//ボールが画面の外に出たら、ゲーム終了
	if (mBallPos.y + BALL_SIZE < 0 || mBallPos.y > WINDOW_HEIGHT + BALL_SIZE)
	{
		mIsRunning = false;
	}
}

void GameManager::Draw() {
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

	//ブロックを描画
	for (i = 0; i < mBlockNo; i++)
	{
		for (j = 0; j < mBlockNo; j++)
		{
			SDL_SetRenderDrawColor(mRenderer, 125, 125, 125, 255);
			SDL_Rect block{ (j + 1) * BLOCK_X_START, (i + 1) * BLOCK_Y_START - (100 * i), BLOCK_WIDTH, BLOCK_HEIGHT };
			SDL_RenderFillRect(mRenderer, &block);
		}
	}

	//パドルを描画
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_Rect paddle1{ static_cast<int>(mPaddlePos[0].x), static_cast<int>(mPaddlePos[0].y), PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_Rect paddle2{ static_cast<int>(mPaddlePos[1].x), static_cast<int>(mPaddlePos[1].y), PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_RenderFillRect(mRenderer, &paddle1);
	SDL_RenderFillRect(mRenderer, &paddle2);

	//ボールを描画
	SDL_Rect ball{ static_cast<int>(mBallPos.x), static_cast<int>(mBallPos.y), BALL_SIZE, BALL_SIZE };
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer);	//バッファ切り替え（バックバッファの情報をフロントバッファに描画）
}

void GameManager::GameEnd() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void GameManager::SceneChanger() {

}

void GameManager::GameClear() {

}

void GameManager::GameOver() {

}

bool GameManager::getIsRunning() {
	return this->mIsRunning;
}

void GameManager::setIsRunning(bool mIsRunning) {
	this->mIsRunning = mIsRunning;
}
