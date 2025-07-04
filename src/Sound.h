#pragma once
#ifndef ZENITHSTG_SRC_SOUND_H_
#define ZENITHSTG_SRC_SOUND_H_

#include "Global.h"
#include "Main.h"

#define SOUND_BGM_HANDLER_NUM 256
#define SOUND_EFFECT_HANDLER_NUM 256
#define SOUND_VOICES 32

class Sound {
public:
	std::array<int, SOUND_BGM_HANDLER_NUM> BGMHandler;
	//SEHandler[][]
	std::array<std::array<int, SOUND_EFFECT_HANDLER_NUM>, SOUND_VOICES> SEHandler;

	std::array<int, SOUND_EFFECT_HANDLER_NUM> SEVoiceIndex = { 0 };

	std::array<int, SOUND_EFFECT_HANDLER_NUM> SEReservation = { 0 };

	void PlayBGM(int ID);
	void PlaySE(int ID);
	void ReserveSE(int ID);
	void ReservePlaySE();
	void SoundLoad();
private:
	void SEAdd(int ID, std::string path);
};

#endif