//ウィンドウの幅
const int WINDOW_WIDTH = 1000;

//ウィンドウの高さ
const int WINDOW_HEIGHT = 800;

//ゲーム画面の幅
const int GAME_SCREEN_WIDTH = 800;

//ブロックの幅
const int BLOCK_WIDTH = 90;

//ブロックの高さ
const int BLOCK_HEIGHT = 30;

//ブロックのX座標(１番左上のブロック)
const int BLOCK_FIRST_DRAW_POS_X = 100;

//ブロックのY座標(１番左上のブロック)
const int BLOCK_FIRST_DRAW_POS_Y = 500;

//ブロックとブロックの間隔(左右)
const int BETWEEN_BLOCKS_WIDTH = 25;

//ブロックとブロックの間隔(上下)
const int BETWEEN_BLOCKS_HEIGHT = 10;

struct BALL
{
    double X,Y,R,DirX,DirY;
    float Speed;
} ball[2];

struct PADDLE
{
    double X,Y,W,H;
    int Length;
} paddle[2];

struct BLOCK
{
    int X, Y;
    unsigned int Visible : 1;
} block[6][6];


/*関数プロトタイプ宣言*/
void DrawBlock(void);
void DrawPlayerInfo(void);
void DrawBall_Paddle(void);
void DrawScreenText(int state);
void Initialize(void);  //初期化
int MainLoop(void);    //メインループ
int GameClear(void);       //ゲームクリア関数
int GameOver(void);        //ゲームオーバー関数
int SelectStageData(void); //ステージデータ選択関数
void LoadStageData(void);  //ステージデータを生成する関数
double Distance(double lineX1, double lineY1, double lineX2, double lineY2, double dotX, double dotY);
