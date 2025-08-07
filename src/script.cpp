#include "script.h"

#include "background.h"
#include "bullet.h"
#include "enemy.h"
#include "math_tool.h"
#include "laser.h"
#include "utility.h"

namespace zenithstg {
	std::array<Script, kStageNum> scripts;
	int num = 4;

	void Script::RunScript() {
		switch (id_) {
		case 0: {
			if (t == 1) {
				sound_mng_.PlayBgm(kBgm1, DX_PLAYTYPE_BACK);
			}
			//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
			if (t >= Beat2Frame(160, 4) && t < Beat2Frame(160, 68)) screen_size_rate = Easing(EaseType::kEaseInQuad, EasingTimeCalc(t, Beat2Frame(160, num - 1), Beat2Frame(160, num)), 1.01, 1.0);
			if (t >= Beat2Frame(160, 68)) screen_size_rate = Easing(EaseType::kEaseInQuad, EasingTimeCalc(t, Beat2Frame(160, num - 1), Beat2Frame(160, num)), 1.05, 1.0);
			if (t >= Beat2Frame(160, 64) && t < Beat2Frame(160, 65)) {
				screen_size_rate = 1.5;
				CameraMove(player_.pos_);
			}
			if (t >= Beat2Frame(160, 65) && t < Beat2Frame(160, 66)) {
				screen_size_rate = 2.0;
				CameraMove(player_.pos_);
			}
			if (t >= Beat2Frame(160, 66) && t < Beat2Frame(160, 67)) {
				screen_size_rate = 2.5;
				CameraMove(player_.pos_);
			}
			if (t >= Beat2Frame(160, 67) && t < Beat2Frame(160, 68)) {
				screen_size_rate = Easing(EaseType::kEaseInQuad, EasingTimeCalc(t, Beat2Frame(160, 67), Beat2Frame(160, 68)), 5.0, 1.0);
				CameraMove(player_.pos_);
			}
			if (t == Beat2Frame(160, 68)) {
				screen_pos_offset = Vec2D(0, 0);
				screen_size_rate = 1.0;
			}
			if (t == Beat2Frame(160, num)) {
				num++;
				double angle = Rad(static_cast<double>(rng() % 36000) / 100.0f);
				CreateSmartBulletGroup(ObjectParams{
					.pos = Vec2D(kCenterX, 180),
					.color = GamingColor(),
					.style = BulletType::kBulletMedium,
					.blend = BlendType::kBlendAdd,
					.pal = 255,
					.start_col_size = 16,
					.end_col_size = 16,
					.start_size = 1,
					.end_size = 1,
					.way = 32,
					.spread = kTau,
					.start_angle = angle,
					.end_angle = angle,
					.start_speed = 0,
					.end_speed = 16,
					.speed_ease_type = EaseType::kLinear,
					.speed_ease_time = 60,
					.se = SoundEffectType::kSoundEffectEnemyShot
					});
			}
			break;
		}
		}
	}
}