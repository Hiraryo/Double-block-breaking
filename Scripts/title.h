/* title.h */
#define TITLE_FONT_SIZE 60
#define FONT_H1 50
#define FONT_H2 40
#define FONT_H3 25
#define FONT_H4 15

typedef struct
{
    double X,Y,Scale;
} slide[5];

typedef struct
{
    double X,Y,R;
} dot[5];

/* タイトル画面 */
void make_screen(const int *windowId, const int *imageId, const int *soundId);

/* 画面の更新を行う関数 */
void update_screen(void);

/* 画面切り替え時のエフェクトを実行する関数 */
void transition_effect(int *radius);

/* 遊ぶモードを選ぶ画面を表示 */
void select_play_mode(int *play_mode);