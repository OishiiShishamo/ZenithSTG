#include "Main.h"

#include "background.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Laser.h"
#include "Script.h"

std::array<Script, kStageNum> scripts;

void
Script::RunScript() {
	switch (id) {
	case 0: {
		//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
		if (t % 1 == 0) {
			/*CreateSmartBulletGroup(ObjectParams{
				.pos = Vec2D(kCenterX, 200),
				.color = GamingColor(),
				.style = kBulletScale,
				.blend = kBlendAdd,
				.pal = 255,
				.start_col_size = 8,
				.end_col_size = 8,
				.start_size = 1,
				.end_size = 1,
				.way = 24,
				.spread = Rad(90),
				.aim = kAimOffset,
				.start_speed = 16,
				.end_speed = 16,
				});
			CreateSmartBulletGroup(ObjectParams{
				.pos = Vec2D(kCenterX - 100, 150),
				.color = GamingColor(),
				.style = kBulletScale,
				.blend = kBlendAdd,
				.pal = 255,
				.start_col_size = 8,
				.end_col_size = 8,
				.start_size = 1,
				.end_size = 1,
				.way = 24,
				.spread = Rad(90),
				.aim = kAimOffset,
				.start_speed = 16,
				.end_speed = 16,
				});
			CreateSmartBulletGroup(ObjectParams{
				.pos = Vec2D(kCenterX + 100, 150),
				.color = GamingColor(),
				.style = kBulletScale,
				.blend = kBlendAdd,
				.pal = 255,
				.start_col_size = 8,
				.end_col_size = 8,
				.start_size = 1,
				.end_size = 1,
				.way = 24,
				.spread = Rad(90),
				.aim = kAimOffset,
				.start_speed = 16,
				.end_speed = 16,
				});*/
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
				.start_angle = Rad(std::sin(Rad(t)) * 360),
				.end_angle = 0,
				.angle_ease_type = kEaseInCubic,
				.angle_ease_time = 60,
				.start_speed = -15,
				.end_speed = 15,
				.speed_ease_type = kEaseInOutCubic,
				.speed_ease_time = 60,
				.se = kSoundEffectEnemyShot,
				});
			/*CreateSmartBulletGroup(ObjectParams{
				.pos = kCenter,
				.color = GamingColor(),
				.style = kBulletLight,
				.blend = kBlendAdd,
				.pal = 255,
				.start_col_size = 16,
				.end_col_size = 16,
				.start_size = 1.0f,
				.end_size = 1.0f,
				.way = 8,
				.aim = 1,
				.start_speed = 8,
				.end_speed = 8,
				});*/
				//CreateBulletGroup(kCenter, GamingColor(), kBulletNormal, kBlendNoblend, 255, 1, 8, 8, 0, 0, 1.0f, 1.0f, 0, 0, 64, TAU, 2, 0, 0, 0, 0, 7, 7, 0, 0);
				//CreateLaserGroup(kCenter, 128, 32, GamingColor(), kBulletScale, kBlendAdd, 255, 1, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 8, TAU, 2, 0, 0, 0, 0, 10, 10, 0, 0);
				//CreateLaserGroup(kCenter, 128, 32, GamingColor(), kBulletLaser, kBlendAdd, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 8, TAU, 0, Rad(sin(Rad(frame)) * 360), 0, kEaseInCubic, 60, -8, 15, kEaseInOutCubic, 60, 0);
		}
		break;
	}
	}
}