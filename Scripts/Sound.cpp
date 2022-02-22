#include "Sound.h"

void Sound::SoundLoad() {

}

bool Sound::BGMPlay(char soundName) {
	this->m_soundName = soundName;
}

bool Sound::BGMStop(char soundName) {
	this->m_soundName = soundName;
}

bool Sound::SEPlay(char soundName) {
	this->m_soundName = soundName;
}