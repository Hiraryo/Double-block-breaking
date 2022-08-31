/**
 * このゲームはブロック崩しです。
 * このソースコードはタイトルのプログラムです。
 * このプログラムのコンパイル方法は、
 * $ hgcc -o title title.c
 * です。
 */
#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include "blockGame.h"

int main(){
    char program[] = "./main";
    int mainWid = HgOpen(WINDOW_WIDTH,WINDOW_HEIGHT);
    int image_1 = HgImageLoad("../Graphics/title.png"); //背景画像
    int soundID_1 = HgSoundLoad("../Sounds/4478.mp3");   //タイトルBGM
    HgSoundVolume(soundID_1,0.4,1);

    //背景画像とタイトルの描画
    HgWImageDraw(mainWid,0,0,image_1);
    int text_layer = HgWAddLayer(mainWid);
    HgLClear(text_layer);
    HgWSetColor(text_layer,HgRGB(0.8, 0.8, 0));
    HgWSetFont(text_layer,HG_M,50);                                    //文字のフォントを明朝、フォントサイズを20に設定
    HgWText(text_layer,WINDOW_WIDTH/2-(3*50),500,"ブロック崩し");        //「ブロック崩し」の文字を描画 6文字
    
    //遊び方説明文
    HgWSetFont(text_layer,HG_M,25);
    HgWSetColor(text_layer,HG_WHITE);
    HgWText(text_layer, WINDOW_WIDTH/2-(2*25+13), 370, "〜遊び方〜");
    HgWText(text_layer, WINDOW_WIDTH/2-(11*25+12), 290, "FキーとJキーで上下にあるパドルを操作します。\n上のパドルは入力方向の反対方向に移動します。");
    HgWSetColor(text_layer,HG_WHITE);
    HgWSetFont(text_layer,HG_M,30);
    HgWText(text_layer,WINDOW_WIDTH/2 - (5*30+15),150,"スペースキーでスタート");
    HgWSetFont(text_layer,HG_M,20);
    HgWText(text_layer,WINDOW_WIDTH/2-(3*20),100,"Qキーで終了");

    // メインループ
    HgSoundPlay(soundID_1);
    HgSetEventMask(HG_KEY_DOWN);    //キー入力のみを検出する
    for (;;){
        hgevent *event_title = HgEventNonBlocking();
        if (event_title != NULL){
            if (event_title -> type == HG_KEY_DOWN){
                switch(event_title -> ch){
                    case ' ':
                        HgSoundStop(soundID_1);
                        HgCloseAll();int result = system(program);
                        return 0;
                    case 'q':
                        HgCloseAll();
                        return 0;
                    default:   continue;
                }
            }
        }
    }
    return 0;
}
