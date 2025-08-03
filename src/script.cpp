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
			if (t % 1 == 0) {
				if (t < 1200) {
					double e_pow_t = std::powf(kE, FastCos(t)), t_pow_5 = std::powf(FastSin(t / 12), 5);
					CreateSmartBulletGroup(ObjectParams{
						.pos = kCenter + Vec2D(
							FastSin(t) * (e_pow_t - 2 * FastCos(t * 4) - t_pow_5),
							FastCos(t) * (e_pow_t - 2 * FastCos(t * 4) - t_pow_5)
						) * 100,
						.color = GamingColor(),
						.style = kBulletScale,
						.blend = kBlendAdd,
						.pal = 255,
						.start_col_size = 8,
						.end_col_size = 8,
						.start_size = 1,
						.end_size = 1,
						.way = 16,
						.spread = Rad(180),
						.start_angle = Rad(t),
						.end_angle = -Rad(t),
						.angle_ease_type = kEaseInCubic,
						.angle_ease_time = 60,
						.start_speed = -3,
						.end_speed = 20,
						.speed_ease_type = kEaseInOutCubic,
						.speed_ease_time = 360,
						.se = kSoundEffectEnemyShot,
						});
				}
				if (t > 1200) {
					CreateSmartBulletGroup(ObjectParams{
						.pos = kCenter,
						.length = 128,
						.width = 32,
						.color = GamingColor(),
						.style = kBulletScale,
						.blend = kBlendAdd,
						.pal = 255,
						.start_col_size = 8,
						.end_col_size = 8,
						.start_size = 1,
						.end_size = 1,
						.way = 48,
						.spread = Rad(180),
						.start_angle = Rad(FastSin(t) * 360),
						.end_angle = 0,
						.angle_ease_type = kEaseInCubic,
						.angle_ease_time = 60,
						.start_speed = -15,
						.end_speed = 15,
						.speed_ease_type = kEaseInOutCubic,
						.speed_ease_time = 60,
						.se = kSoundEffectEnemyShot,
						});
				}
			}
			break;
		}
		}
	}
}