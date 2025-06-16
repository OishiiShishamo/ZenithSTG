#include "Sound.h"

void
Sound::playBGM(int ID) {
	if (isRangeValid(ID, SOUND_BGM_HANDLER_NUM)) {
		return;
	}
	PlaySoundMem(SAFE_ACCESS(BGMHandler, ID), DX_PLAYTYPE_LOOP);
}

void
Sound::playSE(int ID) {
	if (isRangeValid(ID, SOUND_EFFECT_HANDLER_NUM)) {
		return;
	}

	//SE�n���h���������O�o�b�t�@�Ƃ��Ďg���A�����Đ��ɑΉ����Ă���B / Uses a ring buffer per SE to allow concurrent playback.
	PlaySoundMem(SAFE_ACCESS(
		SAFE_ACCESS(SEHandler, ID),
		SAFE_ACCESS(SEVoiceIndex, ID)),
		DX_PLAYTYPE_BACK);

	SAFE_ACCESS(SEVoiceIndex, ID)++;
	if (SAFE_ACCESS(SEVoiceIndex, ID) > SOUND_VOICES)
		SAFE_ACCESS(SEVoiceIndex, ID) = 0;
}