#include "Main.h"

#include "Bullet.h"
#include "Object.h"
#include "Color.h"
#include "Player.h"
#include "Easing.h"

//TODO: à¯êîå∏ÇÁÇµÇΩÉâÉbÉpÅ[ä÷êîçÏÇÈ

std::vector<int> defaultBulletBlend;

void
Bullet::ShowBullet() {
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(posX, posY, size, -showAngle, imgRes.BulletBackGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		DrawRotaGraph(posX, posY, size, -showAngle, imgRes.BulletFrontGH[style], TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawRotaGraph(posX, posY, size, -showAngle, imgRes.BulletBackGH[style], TRUE);
		SetDrawBright(255, 255, 255);
		DrawRotaGraph(posX, posY, size, -showAngle, imgRes.BulletFrontGH[style], TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if (isColShow == 1) {
		if (isCol == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(posX, posY, colSize, GetColor(255, 255, 255), 1);
			DrawFormatString(posX, posY, GetColor(GetColorHSV(std::fmod(frame, 360), 1, 1).r, GetColorHSV(std::fmod(frame, 360), 1, 1).g, GetColorHSV(std::fmod(frame, 360), 1, 1).b), "%f", colSize);
		}
	}
}

void
CreateBullet(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	for (int i = 0; i < Bullets.size(); i++) {
		if (Bullets[i].alive == 0) {
			Bullets[i].alive = 1;
			Bullets[i].isCol = 1;
			Bullets[i].isPlayerShot = 0;
			Bullets[i].posX = x;
			Bullets[i].posY = y;
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
				Bullets[i].startAngle = Plyr.AimPlayer(x, y) + startAngle;
				Bullets[i].endAngle = Plyr.AimPlayer(x, y) + endAngle;
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
			return;
		}
	}
	if (aim == 1) {
		Bullets.emplace_back(1, 1, x, y, Plyr.AimPlayer(x, y) + startAngle, Plyr.AimPlayer(x, y) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
	}
	else {
		Bullets.emplace_back(1, 1, x, y, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
	}
}

void
CreateBulletGroup(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle, spread / way * i + endAngle, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle, spread / way * i + endAngle, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / way / 2, spread / way * i + endAngle + spread / way / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
	default:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle, spread / way * i + endAngle, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime);
		}
		break;
	}
}

void
CreateSimpleBulletGroup(double x, double y, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle, spread / way * i + angle, 0, 0, speed, speed, 0, 0);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle, spread / way * i + angle, 0, 0, speed, speed, 0, 0);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / way / 2, spread / way * i + angle + spread / way / 2, 0, 0, speed, speed, 0, 0);
		}
	default:
		for (int i = 0; i < way; i++) {
			CreateBullet(x, y, color, style, blend, pal, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle, spread / way * i + angle, 0, 0, speed, speed, 0, 0);
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