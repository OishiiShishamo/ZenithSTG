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
	int is_entered = 0;
	void TitleScene::Update() {
		ClearDrawScreen();
		for (int i = 0; i < 256 + std::sin(Rad(t)) * 128; i++) {
			DrawLine(0, 1080 - i, 1920, 1080 - i, (GamingColor() - Easing(EaseType::kEaseInQuad, i / (256 + std::sin(Rad(t)) * 128), 0, 255)).GetDxColor(), 1);
		}
		CreateParticle(Vec2D(rng() % 1920, 1080), GamingColor(180), kParticleRect, kBlendAdd, 255, EaseType::kEaseInQuad, 120, 0, 0, 0, 0, 0, 0.5f, 0.0f, EaseType::kEaseInQuad, 120, 0, Rad(105 - rng() % 30), Rad(105 - rng() % 30), EaseType::kEaseInQuad, 120, 7 + rng() % 5, 0, EaseType::kEaseInQuad, 120);
		MoveParticles();
		DrawFormatStringToHandle(kCenterX - GetDrawFormatStringWidthToHandle(SafeAccess(font_types, kFontUi1), "Press Enter Key.") / 2, kCenterY, Color(kColorWhite).GetDxColor(), SafeAccess(font_types, kFontUi1), "Press Enter Key.");
		
		if (GetAsyncKeyState(VK_RETURN) & (1 << 15) && is_entered == 0) {
			is_entered = 1;
			for (auto& x : particles) {
				x.KillObject();
			}
			scene_manager_.ChangeScene(SceneTypes::kGameScene);
		}
	}
}