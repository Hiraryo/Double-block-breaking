enum
{
    //ウィンドウの幅
    WINDOW_WIDTH = 1000,

    //ウィンドウの高さ
    WINDOW_HEIGHT = 800,

    //ゲーム画面の幅
    GAME_SCREEN_WIDTH = 800,

    //ブロックの幅
    BLOCK_WIDTH = 90,

    //ブロックの高さ
    BLOCK_HEIGHT = 30,

    //ブロックのX座標(１番左上のブロック)
    BLOCK_FIRST_DRAW_POS_X = 100,

    //ブロックのY座標(１番左上のブロック)
    BLOCK_FIRST_DRAW_POS_Y = 500,

    //ブロックとブロックの間隔(左右)
    BETWEEN_BLOCKS_WIDTH = 25,

    //ブロックとブロックの間隔(上下)
    BETWEEN_BLOCKS_HEIGHT = 10
};

struct BALL
{
    double X,Y,R,DirX,DirY;
    float Speed;
};

struct PADDLE
{
    double X,Y,W,H;
    int Length;
};

struct BLOCK
{
    int X, Y;
    unsigned int Visible;
};


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
int LoadStageData(void);  //ステージデータを読み込む関数
double distance(double lineX1, double lineY1, double lineX2, double lineY2, double dotX, double dotY);
