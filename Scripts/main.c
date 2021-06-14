/**
 * このゲームはブロック崩しです。
 * このソースコードはゲームのメインプログラムです。
 * ゲームを始めるたびに、ブロックの配置が変わります。
 * このファイルをコンパイルする際は、
 * $ hgcc -o main main.c
 * としてください。(そうしないとゲームを正常に読み込むことができません)
 * (注)このゲームを始めるには、title.cから実行してください。
 */
#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include <time.h>       //time関数を使うために必要
#include "define.h"

int bar_ball_move(void);    //バーとボールを動かす関数
int game_clear(void);       //ゲームクリア関数
int game_over(void);        //ゲームオーバー関数

doubleLayer layers; //(1)ダブルレイヤの変数を宣言する
doubleLayer layers_ball; //残機のレイヤー
doubleLayer layers_block;   //ブロックのレイヤー
int soundID_1;  //メインBGM
int soundID_2;  //クリアBGM
int soundID_3;  //ゲームオーバーBGM
int SE_1;       //効果音(ボールとブロックが当たったときの音)
int SE_2;       //効果音(ボールとバーが当たったときの音)
int windowID;   //ウィンドウの番号
int layerID;    //レイヤーの番号
int layerID_block;
int block_x = 110, block_y = HEIGHT - 50;    //ブロックの左下座標(x,y)
int i,j;        //ブロックを表示するためのカウント変数
int block_num;//ブロックの数
int bar_x_up = 670,bar_y_up = 750;    //バー(上)の左下X,Y座標
int bar_x_down = 0,bar_y_down = 100;  //バー(下)の左下X,Y座標
int bar_w = 130, bar_h = 20;   //バーの幅と高さ
int ball_x = 200, ball_y = 300;//ボールのX座標とY座標
int ball_dx = 8, ball_dy = 8;//ボールの移動量Xと移動量Y
int ball_r = 16;   //ボールの半径(ball_rの値はball_dx , ball_dyの値の倍数)
int ball_zanki = 2; //ボール残機の初期値(この場合の残機数は３つ)
int score = 0;  //スコア
int block_no = 6;   //ブロックの段数
int block_space_w = 20;  //ブロックとブロックの間隔(左右)
int block_space_h = 10;   //ブロックとブロックの間隔(上下)
int block_line_x = 0;
int block_line_y = 0;   //ブロックの何行目か
int block_dis_y = 0;    //block_dis_yからどれくらい離れているか
char program[] = "./title";
char program2[] = "./ending";
int result;
int block_array[6][6];
FILE *fp;
int stage_no;

int main(){
    srand(time(NULL));
    windowID = HgOpen(WIDTH,HEIGHT);
    soundID_1 = HgSoundLoad("../Sounds/9254.mp3");//ステージBGM
    soundID_2 = HgSoundLoad("../Sounds/Clear1.mp3");//クリア音
    soundID_3 = HgSoundLoad("../Sounds/GAMEOVER.mp3");//ゲームオーバーBGM
    SE_1 = HgSoundLoad("../Sounds/bound.mp3");
    SE_2 = HgSoundLoad("../Sounds/bound2.mp3");
    HgSetEventMask(HG_KEY_DOWN);    //キー入力のみを検出する
    layers = HgWAddDoubleLayer(windowID);  //(2)ダブルレイヤを作成する
    layers_block = HgWAddDoubleLayer(windowID);  //(2)ダブルレイヤを作成する
    HgSoundVolume(soundID_1,1.0,1);
    HgSoundVolume(soundID_2,1.0,0);
    HgSoundVolume(soundID_3,1.0,0);
    HgSoundVolume(SE_1,0.8,0);
    HgSoundVolume(SE_2,0.8,0);
    HgSoundPlay(soundID_1);
    stage_no = rand() % 5;
    stage_no += 1;
    switch (stage_no){
        case 1:
        fp=fopen("../StageDatas/stage1.dat","r");
        break;

        case 2:
        fp=fopen("../StageDatas/stage2.dat","r");
        break;

        case 3:
        fp=fopen("../StageDatas/stage3.dat","r");
        break;

        case 4:
        fp=fopen("../StageDatas/stage4.dat","r");
        break;

        case 5:
        fp=fopen("../StageDatas/stage5.dat","r");
        break;
    }
    if(fp==NULL){
        printf("ファイルがありません\n");
            return -1;
        }
    for(i = 0; i < block_no; i ++){
        for(j = 0; j < block_no; j ++){
            fscanf(fp,"%d",&block_array[i][j]);
            if (block_array[i][j] == 1){
                block_num += 1;
            }
        }
    }
    bar_ball_move();    //バーとボールを動かす関数

    return 0;
}

int bar_ball_move(){
    int image_1 = HgImageLoad("../Graphics/main1.png");
    for (;;){
        //ブロック表示
        layerID_block = HgLSwitch(&layers_block);
        HgLClear(layerID_block);
        for(i = 0; i < block_no; i ++){
            for(j = 0; j< block_no; j ++){
                if (block_array[i][j] != 0){
                    HgWSetFillColor(layerID_block,HG_RED);
                    HgWSetColor(layerID_block,HG_WHITE);
                    HgWSetWidth(layerID_block,2.0);
                    HgWBoxFill(layerID_block,(j+1) * BLOCK_X_START + block_space_w, (i+1) * BLOCK_Y_START + block_space_h - (460 * i),BLOCK_WIDTH,BLOCK_HEIGHT,1);
                }
            }
        }
        //ブロックの当たり判定
        if (ball_y >= 500){
            block_line_x = ((ball_y % 500) / 40);   //ボールが今何行目にあるのかを計算
        }
        if (ball_x >= 100){
            block_line_y = (ball_x / 100 - 1);    //ボールが今何行目にあるのかを計算
        }
        if (ball_y >= BLOCK_Y_START && ball_y <= (BLOCK_HEIGHT * block_no) + (block_space_h * (block_no - 1)) + BLOCK_Y_START){    //ブロックの上またはブロックの下に当たった場合
            if (block_line_x <= 5 && block_line_y <= 5){
                if (block_array[block_line_x][block_line_y] != 0){
                    ball_dy *= -1;
                    block_array[block_line_x][block_line_y] = 0;
                    score += 100;
                    block_num -= 1;
                    HgSoundPlay(SE_1);
                }
            }
        }
        if (block_num == 0){
            HgSoundStop(soundID_1);
            game_clear();
            break;
        }
        layerID = HgLSwitch(&layers);   //(3)レイヤを切り替える
        HgLClear(layerID);                  //レイヤを消去
        HgWImageDraw(layerID,0,0,image_1);
        HgWSetWidth(layerID,7.0);                                       //線の太さを定義
        HgWSetColor(layerID,HG_ORANGE);                                 //線の色を定義
        HgWLine(layerID,GAME_WIDTH,0,GAME_WIDTH,HEIGHT);                //線を描画
        HgWSetFillColor(layerID,HG_GRAY);                               //スコアを表示する背景をグレーに設定
        HgWBoxFill(layerID,GAME_WIDTH,0,WIDTH - GAME_WIDTH,HEIGHT,0);   //スコアを表示する背景をグレーで塗りつぶす
        HgWSetColor(layerID,HG_BLACK);                                  //文字の色を黒に設定
        HgWSetFont(layerID,HG_M,20);                                    //文字のフォントを明朝、フォントサイズを20に設定
        HgWText(layerID,GAME_WIDTH + 20,HEIGHT - 300,"残り : ");            //「残り」の文字を描画
        switch (ball_zanki){
            case 2:
                HgWSetFillColor(layerID,HG_YELLOW);                             //黄色に設定
                HgWSetWidth(layerID,1.0);                                       //線の太さを定義
                HgWCircleFill(layerID,GAME_WIDTH + 50,HEIGHT - 340,ball_r,1);   //ボールの残機数を表示 (１個目)
                HgWCircleFill(layerID,GAME_WIDTH + 100,HEIGHT - 340,ball_r,1);   //ボールの残機数を表示 (２個目)
                HgWCircleFill(layerID,GAME_WIDTH + 150,HEIGHT - 340,ball_r,1);   //ボールの残機数を表示 (３個目)
                break;
            case 1:
                HgWSetFillColor(layerID,HG_YELLOW);                             //黄色に設定
                HgWSetWidth(layerID,1.0);                                       //線の太さを定義
                HgWCircleFill(layerID,GAME_WIDTH + 50,HEIGHT - 340,ball_r,1);   //ボールの残機数を表示 (１個目)
                HgWCircleFill(layerID,GAME_WIDTH + 100,HEIGHT - 340,ball_r,1);   //ボールの残機数を表示 (２個目)
                break;
            case 0:
                HgWSetFillColor(layerID,HG_YELLOW);                             //黄色に設定
                HgWSetWidth(layerID,1.0);                                       //線の太さを定義
                HgWCircleFill(layerID,GAME_WIDTH + 50,HEIGHT - 340,ball_r,1);   //ボールの残機数を表示 (１個目)
                break;
        }
        HgWSetEventMask(windowID,HG_KEY_DOWN);    //キー入力のみを検出する
        hgevent *event = HgEventNonBlocking();     //HandyGraphicのイベントを扱うための変数
        HgWSetFillColor(layerID,HG_YELLOW);
        HgWSetColor(layerID,HG_WHITE);
        HgWSetWidth(layerID,1.0);
        HgWCircleFill(layerID,ball_x,ball_y,ball_r,1);  //ボール(黄色)
        HgWSetFillColor(layerID,HG_BLUE);
        HgWBoxFill(layerID,bar_x_up,bar_y_up,bar_w,bar_h,1);  //バー(青色)
        HgWBoxFill(layerID,bar_x_down,bar_y_down,bar_w,bar_h,1);  //バー(青色)
        HgWSetFont(layerID,HG_M,20);                                    //文字のフォントを明朝、フォントサイズを20に設定
        HgWSetColor(layerID,HG_BLACK);
        HgWText(layerID,GAME_WIDTH + 20,HEIGHT - 100,"SCORE : %d",score);        //「SCORE」の文字を描画
        HgWText(layerID,GAME_WIDTH + 20,HEIGHT - 500,"Fキーで左へ移動");
        HgWText(layerID,GAME_WIDTH + 20,HEIGHT - 550,"Jキーで右へ移動");
        HgWText(layerID,GAME_WIDTH + 20,HEIGHT - 700,"Qキーで終了");
        if (event != NULL){
            if (event -> type == HG_KEY_DOWN){
                switch(event -> ch){
                    case 'f':
                        bar_x_up += 25;
                        bar_x_down -= 25;
                        if (bar_x_up + bar_w >= GAME_WIDTH){
                            bar_x_up = GAME_WIDTH - bar_w;
                        }
                        if (bar_x_down <= 0){
                            bar_x_down = 0;
                        }
                        break;
                    case 'j':
                        bar_x_up -= 25;
                        bar_x_down += 25;
                        if (bar_x_up <= 0){
                            bar_x_up = 0;
                        }
                        if (bar_x_down + bar_w >= GAME_WIDTH){
                            bar_x_down = GAME_WIDTH - bar_w;
                        }
                        break;
                    case 'q':
                        HgClose();
                        return 0;
                    default:   continue;
                }
            }
        }
        ball_x += ball_dx;
        ball_y += ball_dy;
        //横方向の処理
        if (ball_x >= GAME_WIDTH - ball_r || ball_x <= ball_r){
            ball_dx *= -1;
        }
        if (ball_x < 0){
            ball_x = ball_r;
        }
        if (ball_x > GAME_WIDTH - ball_r){
            ball_x = GAME_WIDTH - ball_r;
        }
        //縦方向の処理
        if (ball_y >= HEIGHT - ball_r){ //上
            if (ball_zanki > 0){
                ball_zanki -= 1;
                bar_x_up = 670,bar_y_up = 750;
                bar_x_down = 0; bar_y_down = 100;  //バーの左下X,Y座標
                bar_w = 130; bar_h = 20;   //バーの幅と高さ
                ball_x = 200; ball_dx = 8;//ボールのX座標と移動量X
                ball_y = 300; ball_dy = 8;//ボールのY座標と移動量Y
                bar_ball_move();    //バーとボールを動かす処理
                return 0;
            }
            if (ball_zanki == 0){
                HgSoundStop(soundID_1);
                game_over();
                break;
            }
        }
        if (ball_y < ball_r){  //下
            if (ball_zanki > 0){
                ball_zanki -= 1;
                bar_x_up = 670,bar_y_up = 750;
                bar_x_down = 0; bar_y_down = 100;  //バーの左下X,Y座標
                bar_w = 130; bar_h = 20;   //バーの幅と高さ
                ball_x = 200; ball_dx = 8;//ボールのX座標と移動量X
                ball_y = 300; ball_dy = 8;//ボールのY座標と移動量Y
                bar_ball_move();    //バーとボールを動かす処理
                return 0;
            }
            if (ball_zanki == 0){
                HgSoundStop(soundID_1);
                game_over();
                break;
            }
        }
        if (ball_y < 0){
            ball_y = ball_r;
        }
        if (ball_y > HEIGHT - ball_r){
            ball_y = HEIGHT - ball_r;
        }
        //バーとブロックの当たり判定
            if (ball_x >= bar_x_down - ball_r * 2 && ball_x <= bar_x_down + bar_w + ball_r * 2){    //ボールがバーの左側 + ボールの直径 以上 && ボールがバーの右側 + ボールの直径 以下
                if (ball_y - ball_r == bar_y_down + bar_h || ball_y - ball_r == bar_y_down + bar_h + 4){ //ボールが下+高さ以上
                    ball_dy *= -1;
                    HgSoundPlay(SE_2);
                }
            }
        if (ball_x >= bar_x_up - ball_r * 2 && ball_x <= bar_x_up + bar_w + ball_r * 2){    //ボールがバーの左側 + ボールの直径 以上 && ボールがバーの右側 + ボールの直径 以下
                if (ball_y + ball_r >= bar_y_up){ //ボールが下+高さ以上
                    ball_dy *= -1;
                    HgSoundPlay(SE_2);
                }
            }
        HgSleep(0.03);
    }
return 0;
}

int game_clear(){
        HgClear();
        HgSoundPlay(soundID_2);
        int mas_win = HgAlert("GAME CLEAR!\n\nOKでエンディングへ",NULL,NULL,NULL);
        printf("%d\n",mas_win);
        HgSoundStop(soundID_2);
        HgClose();result = system(program2);
    return 0;
}

int game_over(){
        HgClear();
        HgSoundPlay(soundID_3);
        int mas_win = HgAlert("GAME OVER!\n\nOKでタイトルへ",NULL,NULL,NULL);
        printf("%d\n",mas_win);
        HgSoundStop(soundID_3);
        HgClose();result = system(program);
    return 0;
}
