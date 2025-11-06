#pragma once
#ifndef ZENITHSTG_SRC_GAMESCENE_H_
#define ZENITHSTG_SRC_GAMESCENE_H_

#include "base_scene.h"

namespace zenithstg {
	class GameScene : public BaseScene {
	public:
		void Update() override;
		void Render() override;
	};
}

#endif