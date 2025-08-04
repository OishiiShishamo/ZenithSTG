#include "script.h"

#include "background.h"
#include "bullet.h"
#include "enemy.h"
#include "math_tool.h"
#include "laser.h"
#include "utility.h"

namespace zenithstg {
	std::array<Script, kStageNum> scripts;

	void Script::RunScript() {
		switch (id_) {
		case 0: {
			//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
			if (t % Beat2Frame(140, 1) == 0) {
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
					.way = 16,
					.spread = kTau,
					.start_angle = angle,
					.end_angle = angle,
					.start_speed = 0,
					.end_speed = 32,
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