#pragma once
#ifndef ZENITHSTG_SRC_SCENEMANAGER_H_
#define ZENITHSTG_SRC_SCENEMANAGER_H_

#include <memory>

#include "base_scene.h"
#include "title_scene.h"
#include "game_scene.h"

namespace zenithstg {
	enum SceneTypes {
		kTitleScene = 0,
		kGameScene = 1,
	};

	class SceneManager {
	private:
		std::unique_ptr<BaseScene> now_scene_;
	public:
		SceneManager() {
			now_scene_ = std::make_unique<TitleScene>();
		}

		void Run() {
			now_scene_->Update();
		}

		void Render() {
			now_scene_->Render();
		}

		void ChangeScene(SceneTypes scene) {
			time_mng_.StartTimer();
			switch (scene) {
			case kTitleScene:
				now_scene_.reset(new TitleScene());
				break;
			case kGameScene:
				now_scene_.reset(new GameScene());
				break;
			}
		}
	};
}

#endif  // ZENITHSTG_SRC_SCENEMANAGER_H_