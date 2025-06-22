#include "Main.h"

#include "Background.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Laser.h"
#include "Script.h"

std::array<Script, STAGE_NUM> Scripts;

void
Script::RunScript() {
	switch (ID) {
	case 0: {
		//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
		if (t % 1 == 0) {
			/*CreateSmartBulletGroup(objectParams{
				.pos = Vec2D(CENTER_X, 200),
				.color = GamingColor(),
				.style = B_UROKO,
				.blend = BLEND_ADD,
				.pal = 255,
				.startColSize = 8,
				.endColSize = 8,
				.startSize = 1,
				.endSize = 1,
				.way = 24,
				.spread = Rad(90),
				.aim = AIM_TRUE_OFFSET,
				.startSpeed = 16,
				.endSpeed = 16,
				});
			CreateSmartBulletGroup(objectParams{
				.pos = Vec2D(CENTER_X - 100, 150),
				.color = GamingColor(),
				.style = B_UROKO,
				.blend = BLEND_ADD,
				.pal = 255,
				.startColSize = 8,
				.endColSize = 8,
				.startSize = 1,
				.endSize = 1,
				.way = 24,
				.spread = Rad(90),
				.aim = AIM_TRUE_OFFSET,
				.startSpeed = 16,
				.endSpeed = 16,
				});
			CreateSmartBulletGroup(objectParams{
				.pos = Vec2D(CENTER_X + 100, 150),
				.color = GamingColor(),
				.style = B_UROKO,
				.blend = BLEND_ADD,
				.pal = 255,
				.startColSize = 8,
				.endColSize = 8,
				.startSize = 1,
				.endSize = 1,
				.way = 24,
				.spread = Rad(90),
				.aim = AIM_TRUE_OFFSET,
				.startSpeed = 16,
				.endSpeed = 16,
				});*/
			CreateSmartBulletGroup(objectParams{
				.pos = CENTER,
				.length = 128,
				.width = 32,
				.color = GamingColor(),
				.style = B_UROKO,
				.blend = BLEND_ADD,
				.pal = 255,
				.startColSize = 8,
				.endColSize = 8,
				.startSize = 1,
				.endSize = 1,
				.way = 48,
				.spread = Rad(180),
				.startAngle = Rad(std::sin(Rad(t)) * 360),
				.endAngle = 0,
				.angleEaseType = EASEINCUBIC,
				.angleEaseTime = 60,
				.startSpeed = -15,
				.endSpeed = 15,
				.speedEaseType = EASEINOUTCUBIC,
				.speedEaseTime = 60,
				.SE = SE_ENEMY_SHOT,
				});
			/*CreateSmartBulletGroup(objectParams{
				.pos = CENTER,
				.color = GamingColor(),
				.style = B_LIGHT,
				.blend = BLEND_ADD,
				.pal = 255,
				.startColSize = 16,
				.endColSize = 16,
				.startSize = 1.0f,
				.endSize = 1.0f,
				.way = 8,
				.aim = 1,
				.startSpeed = 8,
				.endSpeed = 8,
				});*/
			//CreateBulletGroup(CENTER, GamingColor(), B_NORMAL, BLEND_NOBLEND, 255, 1, 8, 8, 0, 0, 1.0f, 1.0f, 0, 0, 64, TAU, 2, 0, 0, 0, 0, 7, 7, 0, 0);
			//CreateLaserGroup(CENTER, 128, 32, GamingColor(), B_UROKO, BLEND_ADD, 255, 1, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 8, TAU, 2, 0, 0, 0, 0, 10, 10, 0, 0);
			//CreateLaserGroup(CENTER, 128, 32, GamingColor(), B_LASER, BLEND_ADD, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 8, TAU, 0, Rad(sin(Rad(frame)) * 360), 0, EASEINCUBIC, 60, -8, 15, EASEINOUTCUBIC, 60, 0);
		}
		break;
	}
	}
}