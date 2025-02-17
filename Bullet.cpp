#include "Main.h"

#include "Bullet.h"
#include "Object.h"
#include "Color.h"
#include "Player.h"
#include "Easing.h"

//TODO: 引数減らしたラッパー関数作る

std::vector<int> defaultBulletBlend;

void
Bullet::ShowBullet() {
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.BulletBackGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.BulletFrontGH[style], TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.BulletBackGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		DrawRotaGraph(pos.x, pos.y, size, -showAngle, imgRes.BulletFrontGH[style], TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if (isCol == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(pos.x, pos.y, colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(pos.x, pos.y, GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
		}
	}
}

void
CreateBullet(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	for (int i = 0; i < Bullets.size(); i++) {
		if (Bullets[i].alive == 0) {
			Bullets[i].alive = 1;
			Bullets[i].isCol = isCol;
			Bullets[i].objType = OBJECT_BULLET;
			Bullets[i].pos = pos;
			Bullets[i].color = color;
			Bullets[i].style = style;
			Bullets[i].blend = blend;
			Bullets[i].pal = pal;
			Bullets[i].startColSize = startColSize;
			Bullets[i].endColSize = endColSize;
			Bullets[i].colSizeEaseType = colSizeEaseType;
			Bullets[i].colSizeEaseTime = colSizeEaseTime;
			Bullets[i].startSize = startSize;
			Bullets[i].endSize = endSize;
			Bullets[i].sizeEaseType = sizeEaseType;
			Bullets[i].sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				Bullets[i].startAngle = Plyr.AimPlayer(pos) + startAngle;
				Bullets[i].endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				Bullets[i].startAngle = startAngle;
				Bullets[i].endAngle = endAngle;
			}
			Bullets[i].angleEaseType = angleEaseType;
			Bullets[i].angleEaseTime = angleEaseTime;
			Bullets[i].startSpeed = startSpeed;
			Bullets[i].endSpeed = endSpeed;
			Bullets[i].speedEaseType = speedEaseType;
			Bullets[i].speedEaseTime = speedEaseTime;
			Bullets[i].popFrame = frame;
			Bullets[i].length = 0;
			Bullets[i].width = 0;
			return;
		}
	}
	if (aim == 1) {
		Bullets.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
	}
	else {
		Bullets.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
	}
}

void
CreateBulletGroup(Vec2D pos, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle, spread / way * i + endAngle, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle, spread / way * i + endAngle, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / way / 2, spread / way * i + endAngle + spread / way / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
	default:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle, spread / way * i + endAngle, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
		break;
	}
}

void
CreateSimpleBulletGroup(Vec2D pos, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle, spread / way * i + angle, 0, 0, speed, speed, 0, 0);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle, spread / way * i + angle, 0, 0, speed, speed, 0, 0);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / way / 2, spread / way * i + angle + spread / way / 2, 0, 0, speed, speed, 0, 0);
		}
	default:
		for (int i = 0; i < way; i++) {
			CreateBullet(pos, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle, spread / way * i + angle, 0, 0, speed, speed, 0, 0);
		}
		break;
	}
}

void
MoveBullets() {
	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i].MoveObject();
		Bullets[i].ShowBullet();
	}
	if (frame % 10 == 0) {
		std::sort(Bullets.begin(), Bullets.end(), [](const Bullet& a, const Bullet& b) {
			return a.popFrame < b.popFrame;
		});
		for (int i = 0; i < Bullets.size(); i++) {
			if (Bullets[i].alive == 0) {
				Bullets.erase(Bullets.begin() + i);
			}
		}
	}
}