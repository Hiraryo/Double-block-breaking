/* playerData.h */
/* プレイデータを操作する関数 */
void load_player_data(int *lv, int *hiscore);
void save_player_data(int *lv, int *hiscore);
void update_hiScore(int *score, int *hiscore);
void reset_player_data(int *lv, int *score, int *hiscore);
