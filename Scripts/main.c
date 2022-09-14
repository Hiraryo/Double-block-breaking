/* main.c */
#include "blockGame.h"
#include "playerData.h"
#include "title.h"
#include <stdio.h>
#include <stdlib.h>
#include <handy.h>

int main(){
    //プレイデータを読み込む
    int lv = 0,hiscore = 0;
    load_player_data(&lv, &hiscore);

    //Playerの実体を作成
    Player *player = make_player(lv,0,hiscore);
    if(player == NULL)  return 1;    //異常終了
    
    int mainWind = HgOpen(WINDOW_WIDTH, WINDOW_HEIGHT);
    int title_layer;
    int image_1 = HgImageLoad("../Graphics/title.png"); //背景画像
    int title_bgm = HgSoundLoad("../Sounds/4478.mp3");   //タイトルBGM
    int transition_effect_radius = 0;
    int play_mode = 0;
    HgWSetEventMask(mainWind,HG_KEY_DOWN);
    
    TitleScreen *title_screen = make_title_screen(title_layer, image_1, title_bgm);
    if(title_screen == NULL) return 1;
    make_screen(&mainWind, &image_1, &title_bgm);
    
    for(;;){
        if(transition_effect_radius < WINDOW_WIDTH/2+500){
            update_screen();
        }
        hgevent *inputKeyEvent = HgEventNonBlocking();
        if(inputKeyEvent != NULL){
            if(inputKeyEvent -> type == HG_KEY_DOWN){
                switch (inputKeyEvent -> ch)
                {
                case 'q':
                    //アプリケーション終了
                    HgCloseAll();
                    free(player);
                    return 0;
                case ' ':
                    HgSoundVolume(title_bgm,0.4,1);
                    transition_effect(&transition_effect_radius);
                    break;
                }
            }
        }
        HgSleep(0.016);
    }
    
    return 0;
}
