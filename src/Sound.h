#pragma once
#ifndef SOUND_H
#define SOUND_H

#include "Global.h"
#include "Main.h"

class Sound {
public:
	std::array<int, SOUND_BGM_HANDLER_NUM> BGMHandler;
	std::array<std::array<int, SOUND_VOICES>, SOUND_EFFECT_HANDLER_NUM> SEHandler;

	std::array<int, SOUND_EFFECT_HANDLER_NUM> SEVoiceIndex = { 0 };

	void playBGM(int ID);
	void playSE(int ID);
};

#endif