#include "sound.h"

#include "DxLib.h"

#include "global.h"
#include "property.h"
#include "utility.h"
#include "lua_mng.h"

namespace zenithstg {
	Sound sound_mng_;

	void Sound::PlayBgm(int id, int play_type) {
		if (isRangeValid(id, kSoundBgmHandlerNum)) {
			return;
		}
		PlaySoundMem(SafeAccess(bgm_handler_, id), play_type);
	}

	void Sound::PlaySe(int id) {
		if (isRangeValid(id, kSoundEffectHandlerNum)) {
			return;
		}

		//SEハンドラをリングバッファとして使い、同時再生に対応している。 / Uses a ring buffer per SE to allow concurrent playback.
		PlaySoundMem(SafeAccess(
			SafeAccess(se_handler_, id),
			SafeAccess(se_voice_index_, id)),
			DX_PLAYTYPE_BACK);

		SafeAccess(se_voice_index_, id)++;
		if (SafeAccess(se_voice_index_, id) > kSoundVoices)
			SafeAccess(se_voice_index_, id) = 0;
	}

	void Sound::ReserveSe(int id) {
		if (isRangeValid(id, kSoundEffectHandlerNum)) {
			return;
		}
		SafeAccess(se_reservation_, id) = 1;
	}

	void Sound::ReservePlaySe() {
		int i = 0;
		for (auto& R : se_reservation_) {
			if (R == 1) {
				R = 0;
				PlaySe(i);
			}
			i++;
		}
	}

	void Sound::SoundLoad() {
		SeAdd(kSoundEffectGraze, "res/snd/SE/SE_Graze.wav");
		SeAdd(kSoundEffectPlayerHit, "res/snd/SE/SE_PlayerHit.wav");
		SeAdd(kSoundEffectEnemyShot, "res/snd/SE/SE_EnemyShot.wav");
		BgmAdd(kBgm1, "res/snd/BGM/BGM_Super Extreme.wav");
	}

	void Sound::BgmAdd(int id, std::string path) {
		if (isRangeValid(id, kSoundEffectHandlerNum)) {
			return;
		}
		SafeAccess(bgm_handler_, id) = LoadSoundMem(path.c_str());
		ChangeVolumeSoundMem(static_cast<int>(255.0 * properties_.se_volume_ / 100.0), SafeAccess(bgm_handler_, id));
	}

	void Sound::SeAdd(int id, std::string path) {
		if (isRangeValid(id, kSoundEffectHandlerNum)) {
			return;
		}
		for (auto& S : SafeAccess(se_handler_, id)) {
			S = LoadSoundMem(path.c_str());
			ChangeVolumeSoundMem(static_cast<int>(255.0 * properties_.se_volume_ / 100.0), S);
		}
	}

	void LuaSoundInit(sol::state& lua) {
		lua.set_function("play_bgm",
			[](int id, int play_type) { sound_mng_.PlayBgm(id, play_type); });

		lua.set_function("play_se",
			[](int id) { sound_mng_.ReserveSe(id); });
	}
}