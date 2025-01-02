#include "Bullet.h"

//TODO: ˆø”Œ¸‚ç‚µ‚½ƒ‰ƒbƒp[ŠÖ”ì‚é

double angleT, speedT, colSizeT, sizeT;

int defaultBulletBlend[128];

void
Bullet::MoveBullet() {
	if (alive == 1) {
		angleT = (frame * 1.0f - shotFrame * 1.0f) * 1.0f / angleEaseTime * 1.0f;
		if (angleT > 1)angleT = 1;
		switch (angleEaseType) {
		case 0:
			angle = Linear(angleT, startAngle, endAngle) * 1.0f;
			break;
		case 1:
			angle = EaseInQuad(angleT, startAngle, endAngle) * 1.0f;
			break;
		case 2:
			angle = EaseOutQuad(angleT, startAngle, endAngle) * 1.0f;
			break;
		case 3:
			angle = EaseInOutQuad(angleT, startAngle, endAngle) * 1.0f;
			break;
		case 4:
			angle = EaseInCubic(angleT, startAngle, endAngle) * 1.0f;
			break;
		case 5:
			angle = EaseOutCubic(angleT, startAngle, endAngle) * 1.0f;
			break;
		case 6:
			angle = EaseInOutCubic(angleT, startAngle, endAngle) * 1.0f;
			break;
		default:
			angle = Linear(angleT, startAngle, endAngle) * 1.0f;
			break;
		}
		speedT = (frame * 1.0f - shotFrame * 1.0f) * 1.0f / speedEaseTime * 1.0f;
		if (speedT > 1) speedT = 1;
		switch (speedEaseType) {
		case 0:
			speed = Linear(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		case 1:
			speed = EaseInQuad(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		case 2:
			speed = EaseOutQuad(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		case 3:
			speed = EaseInOutQuad(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		case 4:
			speed = EaseInCubic(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		case 5:
			speed = EaseOutCubic(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		case 6:
			speed = EaseInOutCubic(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		default:
			speed = Linear(speedT, startSpeed, endSpeed) * 1.0f;
			break;
		}
		colSizeT = (frame * 1.0f - shotFrame * 1.0f) * 1.0f / colSizeEaseTime * 1.0f;
		if (colSizeT > 1)colSizeT = 1;
		switch (colSizeEaseType) {
		case 0:
			colSize = Linear(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		case 1:
			colSize = EaseInQuad(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		case 2:
			colSize = EaseOutQuad(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		case 3:
			colSize = EaseInOutQuad(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		case 4:
			colSize = EaseInCubic(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		case 5:
			colSize = EaseOutCubic(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		case 6:
			colSize = EaseInOutCubic(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		default:
			colSize = Linear(colSizeT, startColSize, endColSize) * 1.0f;
			break;
		}
		sizeT = (frame * 1.0f - shotFrame * 1.0f) * 1.0f / sizeEaseTime * 1.0f;
		if (sizeT > 1) sizeT = 1;
		switch (sizeEaseType) {
		case 0:
			size = Linear(sizeT, startSize, endSize) * 1.0f;
			break;
		case 1:
			size = EaseInQuad(sizeT, startSize, endSize) * 1.0f;
			break;
		case 2:
			size = EaseOutQuad(sizeT, startSize, endSize) * 1.0f;
			break;
		case 3:
			size = EaseInOutQuad(sizeT, startSize, endSize) * 1.0f;
			break;
		case 4:
			size = EaseInCubic(sizeT, startSize, endSize) * 1.0f;
			break;
		case 5:
			size = EaseOutCubic(sizeT, startSize, endSize) * 1.0f;
			break;
		case 6:
			size = EaseInOutCubic(sizeT, startSize, endSize) * 1.0f;
			break;
		default:
			size = Linear(sizeT, startSize, endSize) * 1.0f;
			break;
		}
		vecX = cos(angle);
		vecY = -sin(angle);
		if (speed >= Plyr.colSize + Plyr.colSize) {
			for (int i = 0; i < std::ceil(Plyr.colSize * 1.0f / speed * 1.0f); i++) {
				posX += vecX * speed / std::ceil(Plyr.colSize / speed) * 1.0f;
				posY += vecY * speed / std::ceil(Plyr.colSize / speed) * 1.0f;
				if (Plyr.RangePlayer(posX, posY) < colSize + Plyr.colSize) {
					Plyr.HitPlayer();
					alive = 0;
				}
				if (posX < BORDER_LEFT - 64.0f * size) alive = 0;
				if (posX > BORDER_RIGHT + 64.0f * size) alive = 0;
				if (posY < BORDER_UP - 64.0f * size) alive = 0;
				if (posY > BORDER_DOWN + 64.0f * size) alive = 0;
			}
		}
		else {
			posX += vecX * speed * 1.0f;
			posY += vecY * speed * 1.0f;
			if (Plyr.RangePlayer(posX, posY) < colSize + Plyr.colSize) {
				Plyr.HitPlayer();
				alive = 0;
			}
			if (posX < BORDER_LEFT - 64.0f * size) alive = 0;
			if (posX > BORDER_RIGHT + 64.0f * size) alive = 0;
			if (posY < BORDER_UP - 64.0f * size) alive = 0;
			if (posY > BORDER_DOWN + 64.0f * size) alive = 0;
		}
		if (blend == -1) {
			SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
			SetDrawBright(color.r, color.g, color.b);
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawRotaGraph(posX, posY, size, -angle, imgRes.BulletBackGH[style], TRUE);
			SetDrawBright(255, 255, 255);
			DrawRotaGraph(posX, posY, size, -angle, imgRes.BulletFrontGH[style], TRUE);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		else {
			SmartSetDrawBlendMode(blend, pal);
			SetDrawBright(color.r, color.g, color.b);
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			DrawRotaGraph(posX, posY, size, -angle, imgRes.BulletBackGH[style], TRUE);
			SetDrawBright(255, 255, 255);
			DrawRotaGraph(posX, posY, size, -angle, imgRes.BulletFrontGH[style], TRUE);
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		if (isColShow == 1) {
			SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			DrawCircle(posX, posY, colSize, GetColor(255, 255, 255), 1);
			SmartSetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
			DrawFormatString(posX, posY, GetColor(255, 255, 255), "%f", colSize);
		}
	}
}

void
CreateBullet(double x, double y, Color color, int style, int blend, int pal, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime) {
	for (int i = 0; i < Bullets.size(); i++) {
		if (Bullets[i].alive == 0) {
			Bullets[i].alive = 1;
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
			Bullets[i].shotFrame = frame;
			return;
		}
	}
	if (aim == 1) {
		Bullets.emplace_back(1, x, y, Plyr.AimPlayer(x, y) + startAngle, Plyr.AimPlayer(x, y) + endAngle, angleEaseType, angleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
	}
	else {
		Bullets.emplace_back(1, x, y, startAngle, endAngle, angleEaseType, angleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame);
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
		Bullets[i].MoveBullet();
	}
	if (frame % 10 == 0) {
		std::sort(Bullets.begin(), Bullets.end(), [](const Bullet& a, const Bullet& b) {
			return a.shotFrame < b.shotFrame;
		});
		for (int i = 0; i < Bullets.size(); i++) {
			if (Bullets[i].alive == 0) {
				Bullets.erase(Bullets.begin() + i);
			}
		}
	}
}