#pragma once
#ifndef ZENITHSTG_SRC_SCENEMANAGER_H_
#define ZENITHSTG_SRC_SCENEMANAGER_H_

#include <memory>

#include "base_scene.h"
#include "title_scene.h"

namespace zenithstg {
	class SceneManager {
	private:
		std::unique_ptr<BaseScene> now_scene_;
	public:
		SceneManager() {
			now_scene_ = std::make_unique<GameScene>();
		}
		void Run() {
			now_scene_->Update();
		}
	};
}

#endif  // ZENITHSTG_SRC_SCENEMANAGER_H_