#include <stdio.h>

//プレイデータを読み込む
void load_player_data(int *lv, int *hiscore){
    FILE *fp = NULL;
    int i1 = 0,i2 = 0;
    fp = fopen("playerlog.txt","r");
    fscanf(fp, "%d %d", &i1, &i2);
    *lv = i1;
    *hiscore = i2;
    fclose(fp);
}

//ハイスコアを更新する
void update_hiScore(const int *score, int *hiscore){
    *hiscore = *score;
}

//プレイヤーレベルとスコアとハイスコアをリセットする
void reset_player_data(int *lv, int *score, int *hiscore){
    *lv = 1;
    *score = 0;
    *hiscore = 0;
}

//プレイデータを保存する
void save_player_data(int *lv, int *hiscore){
    int a,b;
    a = *lv;
    b = *hiscore;
    FILE *fp = NULL;
    fp = fopen("playerlog.txt","w");
    fprintf(fp,"%d %d\n",a, b);
    fclose(fp);
}