#pragma once
#ifndef ZENITHSTG_SRC_TITLESCENE_H_
#define ZENITHSTG_SRC_TITLESCENE_H_

#include <cmath>

#include "DxLib.h"
#include <Windows.h>

#include "base_scene.h"
#include "color.h"
#include "easing.h"
#include "particle.h"
#include "scene_manager.h"
#include "utility.h"

namespace zenithstg {
	class TitleScene : public BaseScene {
	public:
		void Update() override;
	};
}

#endif