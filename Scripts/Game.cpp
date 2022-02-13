#include "Game.h"
#include "SDL_image.h"

const int thickness = 15;
const float paddleH = 100.0f;

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

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
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
		case SDLK_RIGHT:
			//右矢印
			break;

		case SDLK_LEFT:
			//左矢印
			break;


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
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	//前のフレームから16msが経過するまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	//deltatimeは前のフレームとの時刻の差を秒に変換した値
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	//デルタタイムを最大値で制限する
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	//時刻を更新（次のフレームのために）
	mTicksCount = SDL_GetTicks();

	//デルタタイムに基づいてパドルを更新する
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		//パドルが画面から出ないようにする
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (800.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos.y = 800.0f - paddleH / 2.0f - thickness;
		}
	}

	//ボールの位置を更新する。（ボールの位置を速度に応じて動かす）
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	//必要に応じてバウンドさせる
	//パドルと交差したか
	float diff = mPaddlePos.y - mBallPos.y;

	//差の絶対値を取る
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		//もしyの差が十分に小さく
		diff <= paddleH / 2.0f &&
		//ボールが正しいx位置にあり
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		//ボールが左向きに動いていれば
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	//ボールが画面から消えた時の処理
	else if (mBallPos.x <= 0.0f)
	{
		//ゲーム終了
		mIsRunning = false;
	}

	//ボールが右の壁に衝突したとき
	else if (mBallPos.x >= (1000.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	//ボールが上の壁に衝突したとき
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}

	//ボールが下の壁に衝突したとき
	else if (mBallPos.y >= (800 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}
void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);	//バッファクリア色
	SDL_RenderClear(mRenderer);	//バッファクリア色でバッファをクリア
	
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);	//壁を描画
	
	//画面上の壁
	SDL_Rect wall{
		0,			//左上隅のx
		0,			//左上隅のy
		1000,		//幅
		thickness	//高さ
	};
	SDL_RenderFillRect(mRenderer, &wall);	//長方形を描く（SDL_Rect型の壁をポインタで渡す）

	//画面下の壁
	wall.y = 800 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//画面右の壁
	wall.x = 1000 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1000;
	SDL_RenderFillRect(mRenderer, &wall);

	//パドルを描画
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//ボールを描画
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),	//static_cast<int>で、floatからint整数に変換する。（SDL_Rectはintを使うため）
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
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