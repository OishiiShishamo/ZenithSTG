#include "title_scene.h"

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
	void TitleScene::Update() {
		ClearDrawScreen();
		for (int i = 0; i < 256 + std::sin(Rad(t)) * 128; i++) {
			DrawLine(
				0, 
				1080 - i, 
				1920, 
				1080 - i, 
				(GamingColor() * Easing(EaseType::kEaseInQuad, i / (256 + std::sin(Rad(t)) * 128), 1.0f, 0.0f)).GetDxColor()
			);
		}
		CreateParticle(Vec2D(rng() % 1920, 1080), GamingColor(180), kParticleRect, kBlendAdd, 255, EaseType::kEaseInQuad, 120, 0, 0, 0, 0, 0, 0.5f, 0.0f, EaseType::kEaseInQuad, 120, 0, Rad(105 - rng() % 30), Rad(105 - rng() % 30), EaseType::kEaseInQuad, 120, 7 + rng() % 5, 0, EaseType::kEaseInQuad, 120);
		MoveParticles();
		DrawFormatStringToHandle(kCenterX - GetDrawFormatStringWidthToHandle(SafeAccess(font_types, kFontUi1), "Press Enter Key.") / 2, kCenterY, Color(kColorWhite).GetDxColor(), SafeAccess(font_types, kFontUi1), "Press Enter Key.");
		
		if (GetAsyncKeyState(VK_RETURN) & (1 << 15)) {
			for (auto& x : particles) {
				x.KillObject();
			}
			scene_manager_.ChangeScene(SceneTypes::kGameScene);
		}
	}
}