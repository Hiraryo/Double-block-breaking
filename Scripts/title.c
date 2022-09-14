#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include <stdbool.h>
#include "title.h"
#include "blockGame.h"

doubleLayer title_screen_doubleLayer;
int title_logo_layer;
int transition_effect_layer;
float posX = WINDOW_WIDTH/2-3*TITLE_FONT_SIZE;
float posY = WINDOW_HEIGHT-TITLE_FONT_SIZE*3;
int speed = 10;
int radius = 0;

void make_screen(const int *windowId, const int *imageId, const int *soundId){
    //char program[] = "./main";
    title_screen_doubleLayer = HgWAddDoubleLayer(*windowId);
    float bgm_volume = 1.0;
    HgWImageDraw(*windowId,0,0,*imageId);
    HgSoundVolume(*soundId,bgm_volume,1);
    HgSoundPlay(*soundId);
    HgSetFillColor(HgRGBA(0.25,0.25,0.25,0.5));
    HgBoxFill(0,70,WINDOW_WIDTH,70,0);
    HgSetColor(HG_WHITE);
    HgSetFont(HG_H,FONT_H3);
    HgText(WINDOW_WIDTH/2-7*FONT_H3,105,"スペースキーを押してスタート！");
    HgSetColor(HG_GRAY);
    HgSetFont(HG_H,FONT_H4);
    HgText(WINDOW_WIDTH/2-3*FONT_H4,80,"Qキーで終了");
}

void update_screen(void){
    title_logo_layer = HgLSwitch(&title_screen_doubleLayer);
    HgLClear(title_logo_layer);
    HgWSetColor(title_logo_layer,HG_WHITE);
    HgWSetFont(title_logo_layer,HG_H,TITLE_FONT_SIZE);
    HgWText(title_logo_layer,posX,posY,"ブロック崩し");
    posX -= speed;
    if(posX < 0 || posX+TITLE_FONT_SIZE*6 > WINDOW_WIDTH){
        speed *= -1;
    }
}

void transition_effect(int *radius){
    while (*radius < WINDOW_WIDTH/2+500)
    {
        transition_effect_layer = HgLSwitch(&title_screen_doubleLayer);
        HgLClear(transition_effect_layer);
        HgWSetFillColor(transition_effect_layer,HgRGB(0.05,0.05,0.05));
        HgWCircleFill(transition_effect_layer,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,*radius,0);
        (*radius)++;
    }
}

void select_play_mode(int *play_mode){
    printf("モード選択\n");
    *play_mode = 2;
    printf("2を選択\n");
}