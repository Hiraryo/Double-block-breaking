#include "blockGame.h"
#include <stdlib.h>

//プレイヤーの実体を作成する
Player *make_player(int lv, int score, int hiscore){
    Player *player = malloc(sizeof(Player));
    if(player != NULL){
        player->lv = lv;
        player->score = score;
        player->hiscore = hiscore;
    }
    return player;
}

//パドルの実体を作成する
Paddle *make_paddle(int x, int y, int w, int h){
    Paddle *paddle = malloc(sizeof(Paddle));
    if(paddle != NULL){
        paddle->x = x;
        paddle->y = y;
        paddle->w = w;
        paddle->h = h;
    }
    return paddle;
}

//ボールの実体を作成する
Ball *make_ball(int x, int y, int r, float speed){
    Ball *ball = malloc(sizeof(Ball));
    if(ball != NULL){
        ball->x = x;
        ball->y = y;
        ball->r = r;
        ball->speed = speed;
    }
    return ball;
}

//タイトル画面の実体を作成する
TitleScreen *make_title_screen(int layer, int back_ground, int bgm){
    TitleScreen *title_screen = malloc(sizeof(TitleScreen));
    if(title_screen != NULL){
        title_screen->layer = layer;
        title_screen->back_ground = back_ground;
        title_screen->bgm = bgm;
    }
    return title_screen;
}