/**
 * このゲームはブロック崩しです。
 * このソースコードはエンディングのプログラムです。
 * このプログラムのコンパイル方法は、
 * $ hgcc -o ending ending.c
 * です。
 **/
#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include "blockGame.h"

doubleLayer layers;

int soundID_1;
int windowID;
int layerID;
int txt_y = -600;
char program[] = "./title";
int result;


int main(){
    windowID = HgOpen(WINDOW_WIDTH,WINDOW_HEIGHT);
    soundID_1 = HgSoundLoad("../Sounds/9351.mp3");
    layers = HgWAddDoubleLayer(windowID);
    int image_1 = HgImageLoad("../Graphics/ending.png");
    HgSoundVolume(soundID_1,1.0,1);
    HgSoundPlay(soundID_1);
    for(;;){
        HgWSetEventMask(windowID,HG_KEY_DOWN);    //キー入力のみを検出する
        hgevent *event = HgEventNonBlocking();     //HandyGraphicのイベントを扱うための変数
        hgevent *event2 = HgEventNonBlocking();
        layerID = HgLSwitch(&layers);   //(3)レイヤを切り替える
        HgLClear(layerID);
        HgWImageDraw(layerID,0,0,image_1);
        HgWSetFont(layerID,HG_M,40);                                    //文字のフォントを明朝、フォントサイズを20に設定
        HgWSetColor(layerID,HG_WHITE);
        HgWText(layerID,300,txt_y,"メインプログラミング\n平井　崚太\n\nゲームプログラミング\n平井　崚太\n\nBGM提供\nDOVA-SYNDROME 様\nまっすー　様\n\nSE制作\n平井　崚太\n\n画像制作\n平井　崚太");
        txt_y ++;
        if (txt_y >= 830){
            HgWText(layerID,200,390,"スペースキーを押してください。\n(タイトルへ戻ります。)");
        }
        if (event != NULL){
                if (event -> type == HG_KEY_DOWN){
                    switch(event -> ch){
                        case ' ': 
                            if (txt_y >= 830) {
                                HgSoundStop(soundID_1);
                                HgCloseAll();result = system(program);
                                return 0;
                            }
                            break;
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
    