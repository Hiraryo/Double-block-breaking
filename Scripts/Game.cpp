#include "Game.h"
#include "SDL_image.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
	:mWindow(nullptr)	//�������q���X�g�iconst�ϐ��̏������j
	,mRenderer(nullptr)
	,mIsRunning(true)
	,mTicksCount(0)
{

}

bool Game::Initialize()	//�������`����
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

//�Q�[�����[�v
void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

//�L�[����
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDLK_RIGHT:
			//�E���
			break;

		case SDLK_LEFT:
			//�����
			break;


		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	
	//�I���L�[���������Ƃ��̏���
	const Uint8* state = SDL_GetKeyboardState(NULL);	//�L�[�{�[�h�S�̂̏�Ԃ��i�[�����z��ւ̃|�C���^��Ԃ�
	if (state[SDL_SCANCODE_ESCAPE])
	{
		//ESC�L�[�ŏI��
		mIsRunning = false;
	}

	//�p�h���̈ʒu���L�[���͂Ő��䂷��
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
	//�O�̃t���[������16ms���o�߂���܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	//deltatime�͑O�̃t���[���Ƃ̎����̍���b�ɕϊ������l
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	//�f���^�^�C�����ő�l�Ő�������
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	//�������X�V�i���̃t���[���̂��߂Ɂj
	mTicksCount = SDL_GetTicks();

	//�f���^�^�C���Ɋ�Â��ăp�h�����X�V����
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		//�p�h������ʂ���o�Ȃ��悤�ɂ���
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (800.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos.y = 800.0f - paddleH / 2.0f - thickness;
		}
	}

	//�{�[���̈ʒu���X�V����B�i�{�[���̈ʒu�𑬓x�ɉ����ē������j
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	//�K�v�ɉ����ăo�E���h������
	//�p�h���ƌ���������
	float diff = mPaddlePos.y - mBallPos.y;

	//���̐�Βl�����
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		//����y�̍����\���ɏ�����
		diff <= paddleH / 2.0f &&
		//�{�[����������x�ʒu�ɂ���
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		//�{�[�����������ɓ����Ă����
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	//�{�[������ʂ�����������̏���
	else if (mBallPos.x <= 0.0f)
	{
		//�Q�[���I��
		mIsRunning = false;
	}

	//�{�[�����E�̕ǂɏՓ˂����Ƃ�
	else if (mBallPos.x >= (1000.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	//�{�[������̕ǂɏՓ˂����Ƃ�
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}

	//�{�[�������̕ǂɏՓ˂����Ƃ�
	else if (mBallPos.y >= (800 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}
void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);	//�o�b�t�@�N���A�F
	SDL_RenderClear(mRenderer);	//�o�b�t�@�N���A�F�Ńo�b�t�@���N���A
	
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);	//�ǂ�`��
	
	//��ʏ�̕�
	SDL_Rect wall{
		0,			//�������x
		0,			//�������y
		1000,		//��
		thickness	//����
	};
	SDL_RenderFillRect(mRenderer, &wall);	//�����`��`���iSDL_Rect�^�̕ǂ��|�C���^�œn���j

	//��ʉ��̕�
	wall.y = 800 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//��ʉE�̕�
	wall.x = 1000 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1000;
	SDL_RenderFillRect(mRenderer, &wall);

	//�p�h����`��
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//�{�[����`��
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),	//static_cast<int>�ŁAfloat����int�����ɕϊ�����B�iSDL_Rect��int���g�����߁j
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer);	//�o�b�t�@�؂�ւ��i�o�b�N�o�b�t�@�̏����t�����g�o�b�t�@�ɕ`��j
}

//�Q�[���I������
void Game::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}