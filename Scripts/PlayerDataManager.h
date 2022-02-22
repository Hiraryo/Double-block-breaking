#pragma once
#include "SDL.h"

class PlayerDataManager {
private:
	int m_score;
	int m_playCount;

public:
	bool LoadPlayerData();
	bool SavePlayerData();
	int ScoreCalculation();
	int PlayCountCalculation();
};