#include "Sound.h"

Sound soundMng;

void
Sound::PlayBGM(int ID) {
	if (isRangeValid(ID, SOUND_BGM_HANDLER_NUM)) {
		return;
	}
	PlaySoundMem(SAFE_ACCESS(BGMHandler, ID), DX_PLAYTYPE_LOOP);
}

void
Sound::PlaySE(int ID) {
	if (isRangeValid(ID, SOUND_EFFECT_HANDLER_NUM)) {
		return;
	}

	//SEハンドラをリングバッファとして使い、同時再生に対応している。 / Uses a ring buffer per SE to allow concurrent playback.
	PlaySoundMem(SAFE_ACCESS(
		SAFE_ACCESS(SEHandler, ID),
		SAFE_ACCESS(SEVoiceIndex, ID)),
		DX_PLAYTYPE_BACK);

	SAFE_ACCESS(SEVoiceIndex, ID)++;
	if (SAFE_ACCESS(SEVoiceIndex, ID) > SOUND_VOICES)
		SAFE_ACCESS(SEVoiceIndex, ID) = 0;
}

void
Sound::ReservePlaySE() {
	int i = 0;
	for (auto& R : SEReservation) {
		if (R == 1) {
			R = 0;
			PlaySE(i);
		}
		i++;
	}
}

void
Sound::ReserveSE(int ID) {
	if (isRangeValid(ID, SOUND_EFFECT_HANDLER_NUM)) {
		return;
	}
	SAFE_ACCESS(SEReservation, ID) = 1;
}

void
Sound::SoundLoad() {
	SEAdd(SE_GRAZE, "res/snd/SE/SE_Graze.wav");
	SEAdd(SE_PLAYER_HIT, "res/snd/SE/SE_PlayerHit.wav");
	SEAdd(SE_ENEMY_SHOT, "res/snd/SE/SE_EnemyShot.wav");
}

void
Sound::SEAdd(int ID, std::string path) {
	if (isRangeValid(ID, SOUND_EFFECT_HANDLER_NUM)) {
		return;
	}
	for (auto& S : SAFE_ACCESS(SEHandler, ID)) {
		S = LoadSoundMem(path.c_str());
		ChangeVolumeSoundMem(static_cast<int>(255.0 * Properties.SEVolume / 100.0), S);
	}
}