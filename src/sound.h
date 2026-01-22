#pragma once
#ifndef ZENITHSTG_SRC_SOUND_H_
#define ZENITHSTG_SRC_SOUND_H_

#include "DxLib.h"

#include "global.h"
#include "property.h"
#include "utility.h"
#include "lua_mng.h"

namespace zenithstg {
	inline constexpr int kSoundBgmHandlerNum = 256;
	inline constexpr int kSoundEffectHandlerNum = 256;
	inline constexpr int kSoundVoices = 32;

	class Sound {
	public:
		void PlayBgm(int id, int play_type = DX_PLAYTYPE_LOOP);
		void PlaySe(int id);
		void ReserveSe(int id);
		void ReservePlaySe();
		void SoundLoad();
	private:
		std::array<int, kSoundBgmHandlerNum> bgm_handler_;
		std::array<std::array<int, kSoundEffectHandlerNum>, kSoundVoices> se_handler_;
		std::array<int, kSoundEffectHandlerNum> se_voice_index_ = { 0 };
		std::array<int, kSoundEffectHandlerNum> se_reservation_ = { 0 };
		void BgmAdd(int id, std::string path);
		void SeAdd(int id, std::string path);
	};

	void LuaSoundInit(sol::state& lua);
}

#endif