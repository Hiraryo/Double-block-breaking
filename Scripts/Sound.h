#pragma once

class Sound {
private:
	char m_soundName;

public:
	void SoundLoad();
	bool BGMPlay(char soundName);
	bool BGMStop(char soundName);
	bool SEPlay(char soundName);
};