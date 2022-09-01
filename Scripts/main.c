/**
 * このゲームはブロック崩しです。
 * このソースコードはゲームのメインプログラムです。
 * このプログラムのコンパイル方法は、
 * $ hgcc -o main main.c
 * です。
 */
#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "blockGame.h"

FILE *fp;
doubleLayer game_doubleLayer; //ダブルレイヤの変数を宣言する

char program[] = "./title";
char program2[] = "./ending";

int ball_zanki = 3;         //ボール残機数
int soundID_1;     //メインBGM
int soundID_2;     //クリアBGM
int soundID_3;     //ゲームオーバーBGM
int SE_1;          //効果音(ボールとブロックが当たったときの音)
int SE_2;          //効果音(ボールとバーが当たったときの音)
int mainWid;       //メインウィンドウid
int block_num;     //ブロックの数
int score = 0;     //スコア
int result;
int mes_win;
int background_image;
int block_layer,   //ブロックのレイヤー
    player_info_layer, //残機数やスコアを表示するレイヤー
    game_layer,    //ボールやパドルを表示するレイヤー
    game_start_layer;

int main(void){
    
    srand(time(NULL));
    //SelectStageData();    //ステージデータを選択
    LoadStageData();      //ステージデータを読み込む
    mainWid = HgOpen(WINDOW_WIDTH,WINDOW_HEIGHT);
    background_image = HgImageLoad("../Graphics/main1.png");    //ステージ背景
    soundID_1 = HgSoundLoad("../Sounds/9254.mp3");//ステージBGM
    soundID_2 = HgSoundLoad("../Sounds/Clear1.mp3");//クリア音
    soundID_3 = HgSoundLoad("../Sounds/GAMEOVER.mp3");//ゲームオーバーBGM
    SE_1 = HgSoundLoad("../Sounds/bound1.mp3");
    SE_2 = HgSoundLoad("../Sounds/bound2.mp3");
    HgSetEventMask(HG_KEY_DOWN);    //キー入力のみを検出する
    HgSoundVolume(soundID_1,1.0,1);
    HgSoundVolume(soundID_2,1.0,0);
    HgSoundVolume(soundID_3,1.0,0);
    HgSoundVolume(SE_1,0.5,0);
    HgSoundVolume(SE_2,0.5,0);
    HgSoundPlay(soundID_1);

    player_info_layer = HgWAddLayer(mainWid);
    game_start_layer = HgWAddLayer(mainWid);
    block_layer = HgWAddLayer(mainWid);
    game_doubleLayer = HgWAddDoubleLayer(mainWid);
    
    Initialize();
    HgWImageDraw(mainWid,0,0,background_image); //背景画像
    DrawBlock();
    DrawPlayerInfo();
    DrawBall_Paddle();
    MainLoop();
    return 0;
}
/*
//読み込むステージデータを決める
int SelectStageData(void){
    
}
*/

//ステージデータを生成
void LoadStageData(void){
    for(int y=0; y<6; y++){
        for(int x=0; x<6; x++){
            block[y][x].Visible = 1;
        }
    }
}

void Initialize(void){
    ball[0].R = 10;
    ball[1].R = 10;
    paddle[0].W = 130, paddle[0].H = 10;
    paddle[1].W = 130, paddle[1].H = 10;
    paddle[0].X = (GAME_SCREEN_WIDTH-paddle[0].W) / 2, paddle[0].Y = 700;
    paddle[1].X = (GAME_SCREEN_WIDTH-paddle[1].W) / 2, paddle[1].Y = 100;
    ball[0].Speed = 8;
    ball[1].Speed = 7;
    block_num = 1;
    ball[0].X = rand() % GAME_SCREEN_WIDTH, ball[0].Y = 300;
    ball[1].X = rand() % GAME_SCREEN_WIDTH, ball[1].Y = 300;
    ball[0].DirX = (rand() % 2) ? ball[0].Speed:-ball[0].Speed, ball[0].DirY = ball[0].Speed;
    ball[1].DirX = (rand() % 2) ? ball[1].Speed:-ball[1].Speed, ball[1].DirY = ball[1].Speed;
}

//スコアや残機数を描画
void DrawPlayerInfo(void){
    int loop = 0;
    HgLClear(player_info_layer);
    
    HgWSetWidth(player_info_layer,7.0);                                       //線の太さを定義
    HgWSetColor(player_info_layer,HG_ORANGE);                                 //線の色を定義
    HgWLine(player_info_layer,GAME_SCREEN_WIDTH,0,GAME_SCREEN_WIDTH,WINDOW_HEIGHT);                //線を描画
    HgWSetFillColor(player_info_layer,HG_GRAY);                               //スコアを表示する背景をグレーに設定
    HgWBoxFill(player_info_layer,GAME_SCREEN_WIDTH,0,WINDOW_WIDTH - GAME_SCREEN_WIDTH,WINDOW_HEIGHT,0);   //スコアを表示する背景をグレーで塗りつぶす
    HgWSetColor(player_info_layer,HG_BLACK);                                  //文字の色を黒に設定
    HgWSetFont(player_info_layer,HG_M,20);                                    //文字のフォントを明朝、フォントサイズを20に設定
    HgWText(player_info_layer,GAME_SCREEN_WIDTH + 20,WINDOW_HEIGHT - 100,"SCORE : %d",score);        //「SCORE」の文字を描画
    HgWText(player_info_layer,GAME_SCREEN_WIDTH + 20,WINDOW_HEIGHT - 300,"残り : ");            //「残り」の文字を描画
    HgWSetFillColor(player_info_layer,HG_YELLOW);                             //黄色に設定
    HgWSetWidth(player_info_layer,1.0);                                       //線の太さを定義
    while (loop < ball_zanki)
    {
        HgWCircleFill(player_info_layer,GAME_SCREEN_WIDTH + 50+(loop*50),WINDOW_HEIGHT - 340,ball[0].R,1);   //ボールの残機数を表示
        loop++;
    }
    HgWText(player_info_layer,GAME_SCREEN_WIDTH + 20,WINDOW_HEIGHT - 500,"Fキーで左へ移動");
    HgWText(player_info_layer,GAME_SCREEN_WIDTH + 20,WINDOW_HEIGHT - 550,"Jキーで右へ移動");
    HgWText(player_info_layer,GAME_SCREEN_WIDTH + 20,WINDOW_HEIGHT - 700,"Qキーで終了");
}

//ゲームの進行状態の文字を描画
void DrawScreenText(int state){
    HgLClear(game_start_layer);
    
    switch (state)
    {
    case 0:
        HgWSetFont(game_start_layer,HG_M,80);
        HgWSetFillColor(game_start_layer,HgRGBA(0.5, 0.5, 0, 0.5)); //オレンジ
        HgWBoxFill(game_start_layer,0,WINDOW_HEIGHT/3,GAME_SCREEN_WIDTH-4,WINDOW_HEIGHT/3,1);
        HgWSetColor(game_start_layer, HgRGBA(1.0, 1.0, 1.0, 0.5));
        HgWText(game_start_layer, GAME_SCREEN_WIDTH/7, WINDOW_HEIGHT/3+100, "ゲーム開始！！");
        break;
    
    case 1:
        HgWSetFont(game_start_layer,HG_M,80);
        HgWSetFillColor(game_start_layer,HgRGBA(0.8, 0.8, 0.0, 0.6)); //黄色
        HgWBoxFill(game_start_layer,0,WINDOW_HEIGHT/3,GAME_SCREEN_WIDTH-4,WINDOW_HEIGHT/3,1);
        HgWSetColor(game_start_layer, HgRGB(0.1, 0.1, 0.1));
        HgWText(game_start_layer, GAME_SCREEN_WIDTH/8, WINDOW_HEIGHT/3+100, "ゲームクリア！！");
        HgWSetFont(game_start_layer,HG_M,30);
        HgWText(game_start_layer, GAME_SCREEN_WIDTH/5, WINDOW_HEIGHT/3+40, "スペースキーを押してタイトルへ");
        break;

    case 2:
        HgWSetFont(game_start_layer,HG_M,60);
        HgWSetFillColor(game_start_layer,HgRGBA(0.0,0.0,0.0,0.9)); //グレー
        HgWBoxFill(game_start_layer,0,WINDOW_HEIGHT/3,GAME_SCREEN_WIDTH-4,WINDOW_HEIGHT/3,1);
        HgWSetColor(game_start_layer, HG_WHITE);
        HgWText(game_start_layer, GAME_SCREEN_WIDTH/6, WINDOW_HEIGHT/3+100, "Game Over（ ;  ; ）");
        HgWSetFont(game_start_layer,HG_M,30);
        HgWText(game_start_layer, GAME_SCREEN_WIDTH/5, WINDOW_HEIGHT/3+40, "スペースキーを押してタイトルへ");
        break;

    default:
        break;
    }
}

//ブロックを描画
void DrawBlock(void){
    int x,y = 0;
    HgLClear(block_layer);
    
    for(y =0; y < 6; y++){
        for(x = 0; x < 6; x++){
            if(block[y][x].Visible == 1){
                block_num += 1;
                HgWSetFillColor(block_layer,HG_RED);
                HgWSetColor(block_layer,HG_WHITE);
                HgWSetWidth(block_layer,2.0);
                HgWBoxFill(block_layer,(x+1) * BLOCK_FIRST_DRAW_POS_X + BETWEEN_BLOCKS_WIDTH, BLOCK_FIRST_DRAW_POS_Y-(y*50) + BETWEEN_BLOCKS_HEIGHT,BLOCK_WIDTH,BLOCK_HEIGHT,1);
            }
        }
    }
}

//ボールとパドルを描画
void DrawBall_Paddle(void){
    game_layer = HgLSwitch(&game_doubleLayer);
    HgLClear(game_layer);
    HgWSetFillColor(game_layer,HG_YELLOW);
    HgWSetColor(game_layer,HG_WHITE);
    HgWSetWidth(game_layer,1.0);
    HgWCircleFill(game_layer,ball[0].X,ball[0].Y,ball[0].R,1);  //ボール(黄色)
    HgWSetFillColor(game_layer,HG_BLUE);
    HgWCircleFill(game_layer,ball[1].X,ball[1].Y,ball[1].R,1);  //ボール(青色)
    
    HgWBoxFill(game_layer,paddle[0].X,paddle[0].Y,paddle[0].W,paddle[0].H,1);  //上のバー(青色)
    HgWBoxFill(game_layer,paddle[1].X,paddle[1].Y,paddle[1].W,paddle[1].H,1);  //下のバー(青色)
}

int MainLoop(void){
    srand((unsigned int)time(NULL));
    
    HgWSetEventMask(mainWid,HG_KEY_DOWN);    //キー入力のみを検出する
    for (;;){
        //ブロックの当たり判定

        //ボールとパドルを描画
        DrawBall_Paddle();

        //キーボード入力
        hgevent *event = HgEventNonBlocking();     //HandyGraphicのイベントを扱うための変数
        if (event != NULL){
            if (event -> type == HG_KEY_DOWN){
                switch(event -> ch){
                    case 'f':
                        paddle[0].X += 30;
                        paddle[1].X -= 30;
                        if (paddle[0].X + paddle[0].W >= GAME_SCREEN_WIDTH-3){
                            paddle[0].X = GAME_SCREEN_WIDTH - paddle[0].W-3;
                        }
                        if (paddle[1].X <= 0){
                            paddle[1].X = 0;
                        }
                        break;
                    case 'j':
                        paddle[0].X -= 30;
                        paddle[1].X += 30;
                        if (paddle[0].X <= 0){
                            paddle[0].X = 0;
                        }
                        if (paddle[1].X + paddle[1].W >= GAME_SCREEN_WIDTH-3){
                            paddle[1].X = GAME_SCREEN_WIDTH - paddle[1].W-3;
                        }
                        break;

                    case 'q':
                        HgCloseAll();
                        return 0;
                }
            }
        }
        
        if(ball[0].Y > paddle[0].Y-10 || ball[1].Y > paddle[0].Y-10){
            //上のパドルと黄色ボールの当たり判定                                                                       ball[0].X+ball[0].R >= paddle[0].X && ball[0].X-ball[0].R <= paddle[0].X+paddle[0].W
            Distance(paddle[0].X,paddle[0].Y,paddle[0].X+paddle[0].W,paddle[0].Y,ball[0].X,ball[0].Y+ball[0].R) <= 4.0  && ball[0].X+ball[0].R >= paddle[0].X && ball[0].X-ball[0].R <= paddle[0].X+paddle[0].W && ball[0].Y-ball[0].R <= paddle[0].Y && ball[0].DirY > 0 ? ball[0].DirY *= -1,HgSoundPlay(SE_2): ball[0].DirY;
            
            //上のパドルと青色ボールの当たり判定
            Distance(paddle[0].X,paddle[0].Y,paddle[0].X+paddle[0].W,paddle[0].Y,ball[1].X,ball[1].Y+ball[1].R) <= 4.0  && ball[1].X+ball[1].R >= paddle[0].X && ball[1].X-ball[1].R <= paddle[0].X+paddle[0].W  && ball[1].Y-ball[1].R <= paddle[0].Y && ball[1].DirY > 0 ? ball[1].DirY *= -1,HgSoundPlay(SE_2): ball[1].DirY;
        }
        
        if(ball[0].Y < paddle[1].Y+paddle[1].H+10 || ball[1].Y < paddle[1].Y+paddle[1].H+10){
            //下のパドルと黄色ボールの当たり判定                                                                       ball[0].X+ball[0].R >= paddle[1].X && ball[0].X-ball[0].R <= paddle[1].X+paddle[1].W
            Distance(paddle[1].X,paddle[1].Y+paddle[1].H,paddle[1].X+paddle[1].W,paddle[1].Y+paddle[1].H,ball[0].X,ball[0].Y) <= 8.0  && ball[0].X+ball[0].R >= paddle[1].X && ball[0].X-ball[0].R <= paddle[1].X+paddle[1].W && ball[0].Y+ball[0].R >= paddle[1].Y+paddle[1].H && ball[0].DirY < 0 ? ball[0].DirY *= -1,HgSoundPlay(SE_2): ball[0].DirY;
            
            //下のパドルと青色ボールの当たり判定
            Distance(paddle[1].X,paddle[1].Y+paddle[1].H,paddle[1].X+paddle[1].W,paddle[1].Y+paddle[1].H,ball[1].X,ball[1].Y) <= 8.0  && ball[1].X+ball[1].R >= paddle[1].X && ball[1].X-ball[1].R <= paddle[1].X+paddle[1].W && ball[1].Y+ball[1].R >= paddle[1].Y+paddle[1].H && ball[1].DirY < 0 ? ball[1].DirY *= -1,HgSoundPlay(SE_2): ball[1].DirY;
        }
        
        //ボールの移動
        ball[0].X += ball[0].DirX;
        ball[0].Y += ball[0].DirY;

        ball[1].X += ball[1].DirX;
        ball[1].Y += ball[1].DirY;

        //ボールがゲーム画面の左右に行った時の跳ね返り
        if (ball[0].X >= GAME_SCREEN_WIDTH - ball[0].R || ball[0].X <= ball[0].R){
            ball[0].DirX *= -1;
        }

        //ボールがゲーム画面の左端に行った時
        if (ball[0].X-ball[0].R < 0){
            ball[0].X = ball[0].R;
        }

        //ボールがゲーム画面の右端に行った時
        if (ball[0].X+ball[0].R > GAME_SCREEN_WIDTH){
            ball[0].X = GAME_SCREEN_WIDTH - ball[0].R;
        }
        
        //ボールがゲーム画面の上に行った時 || ボールがゲーム画面の下に行った時
        if (ball[0].Y - ball[0].R*2 > WINDOW_HEIGHT || ball[0].Y + ball[0].R*2 < 0){
            ball_zanki -= 1;
            HgLShow(game_start_layer,0);
            HgSoundStop(SE_1);
            HgSoundStop(SE_2);
            if(ball_zanki == -1){
                HgLShow(game_start_layer,1);
                HgLMove(game_start_layer,2);
                HgSoundStop(soundID_1);
                GameOver();
                break;
            }
            Initialize();       //バーとボールの位置とボールの移動方向を初期化
            DrawPlayerInfo();
            MainLoop();         //バーとボールを動かす処理
            return 0;
        }
        
        /*----------------------*/
        //ボールがゲーム画面の左右に行った時の跳ね返り
        if (ball[1].X >= GAME_SCREEN_WIDTH - ball[1].R || ball[1].X <= ball[1].R){
            ball[1].DirX *= -1;
        }

        //ボールがゲーム画面の左端に行った時
        if (ball[1].X-ball[1].R < 0){
            ball[1].X = ball[1].R;
        }

        //ボールがゲーム画面の右端に行った時
        if (ball[1].X+ball[1].R > GAME_SCREEN_WIDTH){
            ball[1].X = GAME_SCREEN_WIDTH - ball[1].R;
        }
        
        //ボールがゲーム画面の上に行った時 || ボールがゲーム画面の下に行った時
        if (ball[1].Y + ball[1].R*2 > WINDOW_HEIGHT || ball[1].Y - ball[1].R*2 < 0){
            ball[1].DirY *= -1;
        }

        HgSleep(0.016);
    }
    return 0;
}

//線分と点の垂線の距離を返す
double Distance(double lineX1, double lineY1, double lineX2, double lineY2, double dotX, double dotY){
    double a, b, c; // ax + by + c = 0
    double root;
    double dist;    // 求める距離

    a = lineY1 - lineY2;
    b = lineX2 - lineX1;
    c = (-b * lineY1) + (-a * lineX1);
    root = sqrt(a*a + b*b);

    if(root == 0.0){
        return -1.0;    // 求められない場合は負の値を返す
    }

    dist = ((a * dotX) + (b * dotY) + c) / root;

    if(dist < 0.0){
        dist = -dist;
    }

    return dist;
}

int GameClear(void){
        HgClear();
        HgSoundPlay(soundID_2);
        mes_win = HgAlert("GAME CLEAR!\n\nOKでエンディングへ","OK",NULL,NULL);
        if(mes_win == 0){
            HgSoundStop(soundID_2);
            HgCloseAll();result = system(program2);
        }
    return 0;
}

int GameOver(void){
        HgSoundPlay(soundID_3);
        DrawScreenText(2);
        for(;;){
            hgevent *event = HgEventNonBlocking();     //HandyGraphicのイベントを扱うための変数
            if (event != NULL){
                if (event -> type == HG_KEY_DOWN){
                    switch(event -> ch){
                        case ' ':
                            //タイトル画面に戻る
                            HgSoundStop(soundID_3);
                            HgCloseAll();result = system(program);
                            return 0;
                        case 'q':
                            //ゲーム終了
                            HgCloseAll();
                            return 0;
                    }
                }
            }
        }
    return 0;
}
