#pragma once
#ifndef ZENITHSTG_SRC_RESLOAD_H_
#define ZENITHSTG_SRC_RESLOAD_H_

namespace zenithstg {
	class ResLoad {
	public:
		void UiGhLoad();
		void BulletGhLoad();
		void ParticleGhLoad();
		void EnemyGhLoad();
		void FaceGhLoad();
		void PlayerGhLoad();
		void ShotGhLoad();
		void FontLoad();
	};
}

#endif