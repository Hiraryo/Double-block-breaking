/**
 * このゲームはブロック崩しです。
 * このソースコードはタイトルのプログラムです。
 * このファイルをコンパイルする際は、
 * $ hgcc -o title title.c
 * としてください。(そうしないとゲームを正常に読み込むことができません)
 * (注)このゲームを始めるには、このプログラムファイルから実行してください。
 */
#include <stdio.h>
#include <handy.h>
#include <stdlib.h>     //rand関数を使うために必要
#include <time.h>       //time関数を使うために必要


#define WIDTH 1000       //ウィンドウの幅
#define HEIGHT 800      //ウィンドウの高さ

doubleLayer layers_title; //(1)ダブルレイヤの変数を宣言する
char program[] = "./main";
int result;

int soundID_1;  //タイトルBGM
int main(){
    int image_1 = HgImageLoad("title.png");
    soundID_1 = HgSoundLoad("4478.mp3");   //タイトルBGM
    HgSoundVolume(soundID_1,1.0,1);
    HgSoundPlay(soundID_1);
    srand(time(NULL));
    int layerID_title;
    int windowID;   //ウィンドウの番号
    int mes_x = 500;    //ゲームタイトルの初期値X
    int mes_y = 400;    //ゲームタイトルの初期値Y
    int mes_dx;  //dxの値を0〜8の乱数値とする; //ゲームタイトルの移動量X
    int mes_dy;  //dyの値を0〜8の乱数値とする; //ゲームタイトルの移動量Y
    int mes_w;
    int mes_h;
    int title_txt_size = 50;
    int title_txt_size_f = 1;

    windowID = HgOpen(WIDTH,HEIGHT);
    layers_title = HgWAddDoubleLayer(windowID);  //(2)ダブルレイヤを作成する
    HgSetEventMask(HG_KEY_DOWN);    //キー入力のみを検出する

    mes_dx = rand() % 10;
    mes_dy = rand() % 10;

    mes_dx += 1;
    mes_dy += 1;
    
    for (;;){
        layerID_title = HgLSwitch(&layers_title);
        HgLClear(layerID_title);
        HgWImageDraw(layerID_title,0,0,image_1);
        if (title_txt_size == 50){
            title_txt_size_f = 1;
        }
        if (title_txt_size == 1){
            title_txt_size_f = 0;
        }
        if (title_txt_size_f == 1){
            title_txt_size --;
        }else if (title_txt_size_f == 0){
            title_txt_size ++;
        }
        mes_w = title_txt_size * 6;
        mes_h = title_txt_size;

        mes_x += mes_dx;
        mes_y += mes_dy;
        //横方向の処理
        if (mes_x >= WIDTH - mes_w || mes_x <= 0){
            mes_dx *= -1;
        }
        if (mes_x < 0){
            mes_x = mes_x;
        }
        if (mes_x > WIDTH - mes_w){
            mes_x = WIDTH - mes_w;
        }
        //縦方向の処理
        if (mes_y >= HEIGHT - mes_h || mes_y <= 0){
            mes_dy *= -1;
        }
        if (mes_y < 0){
            mes_y = mes_y;
        }
        if (mes_y > HEIGHT - mes_h){
            mes_y = HEIGHT - mes_h;
        }
        HgWSetColor(layerID_title,HG_WHITE);
        HgWSetFont(layerID_title,HG_M,title_txt_size);                                    //文字のフォントを明朝、フォントサイズを20に設定
        HgWText(layerID_title,mes_x,mes_y,"ブロック崩し");        //「ブロック崩し」の文字を描画 6文字
        HgWSetFont(layerID_title,HG_M,30);
        HgWText(layerID_title,350,300,"スペースキーでスタート");
        HgWSetFont(layerID_title,HG_M,20);
        HgWText(layerID_title,450,250,"Qキーで終了");
        hgevent *event_title = HgEventNonBlocking();
        if (event_title != NULL){
            if (event_title -> type == HG_KEY_DOWN){
                switch(event_title -> ch){
                    case ' ':
                        HgSoundStop(soundID_1);
                        HgClose();result = system(program);
                        return 0;
                    case 'q':
                        HgClose();
                        return 0;
                    default:   continue;
                }
            }
        }
    }
    return 0;    
}