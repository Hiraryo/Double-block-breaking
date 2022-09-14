//ウィンドウの幅
#define WINDOW_WIDTH 1000
//ウィンドウの高さ
#define WINDOW_HEIGHT 800

//プレイデータの定義
typedef struct Player
{
    int lv, score, hiscore;
} Player;

//パドルの定義
typedef struct Paddle
{
    int x,y,w,h;
} Paddle;

//ボールの定義
typedef struct Ball
{
    int x,y,r;
    float speed;
} Ball;

//タイトル画面
typedef struct TitleScreen
{
    int layer;
    int back_ground;
    int bgm;
} TitleScreen;


/* コンストラクタ */
Player *make_player(int lv, int score, int hiscore);
Paddle *make_paddle(int x, int y, int w, int h);
Ball *make_ball(int x, int y, int r, float speed);
TitleScreen *make_title_screen(int layer, int back_ground, int bgm);