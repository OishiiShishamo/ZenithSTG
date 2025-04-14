#include "Main.h"

#include "Laser.h"
#include "Bullet.h"
#include "Color.h"
#include "Player.h"
#include "Easing.h"

void
Laser::ShowLaser() {
	if (blend == -1) {
		SmartSetDrawBlendMode(defaultBulletBlend[style], pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			pos.x + cos(angle + PI / 2) * width / 2,
			pos.y - sin(angle + PI / 2) * width / 2,
			pos.x + cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y - sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y + sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2,
			pos.y + sin(angle + PI / 2) * width / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletBackGH[style],
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			pos.x + cos(angle + PI / 2) * width / 2,
			pos.y - sin(angle + PI / 2) * width / 2,
			pos.x + cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y - sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y + sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2,
			pos.y + sin(angle + PI / 2) * width / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletFrontGH[style],
			TRUE);
		SmartSetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	else {
		SmartSetDrawBlendMode(blend, pal);
		SetDrawBright(color.r, color.g, color.b);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawRectModiGraph(
			pos.x + cos(angle + PI / 2) * width / 2,
			pos.y - sin(angle + PI / 2) * width / 2,
			pos.x + cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y - sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y + sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2,
			pos.y + sin(angle + PI / 2) * width / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletBackGH[style],
			TRUE);
		SetDrawBright(255, 255, 255);
		DrawRectModiGraph(
			pos.x + cos(angle + PI / 2) * width / 2,
			pos.y - sin(angle + PI / 2) * width / 2,
			pos.x + cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y - sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2 + cos(angle) * length,
			pos.y + sin(angle + PI / 2) * width / 2 - sin(angle) * length,
			pos.x - cos(angle + PI / 2) * width / 2,
			pos.y + sin(angle + PI / 2) * width / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			64 - 128 * drawRatioBulletGraphs[style] / 2,
			128 * drawRatioBulletGraphs[style],
			128 * drawRatioBulletGraphs[style],
			imgRes.BulletFrontGH[style],
			TRUE);
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
CreateLaser(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	for (int i = 0; i < Lasers.size(); i++) {
		if (Lasers[i].alive == 0) {
			Lasers[i].alive = 1;
			Lasers[i].isCol = isCol;
			Lasers[i].objType = OBJECT_LASER;
			Lasers[i].pos = pos;
			Lasers[i].color = color;
			Lasers[i].style = style;
			Lasers[i].blend = blend;
			Lasers[i].pal = pal;
			Lasers[i].startColSize = startColSize;
			Lasers[i].endColSize = endColSize;
			Lasers[i].colSizeEaseType = colSizeEaseType;
			Lasers[i].colSizeEaseTime = colSizeEaseTime;
			Lasers[i].startSize = startSize;
			Lasers[i].endSize = endSize;
			Lasers[i].sizeEaseType = sizeEaseType;
			Lasers[i].sizeEaseTime = sizeEaseTime;
			if (aim == 1) {
				Lasers[i].startAngle = Plyr.AimPlayer(pos) + startAngle;
				Lasers[i].endAngle = Plyr.AimPlayer(pos) + endAngle;
			}
			else {
				Lasers[i].startAngle = startAngle;
				Lasers[i].endAngle = endAngle;
			}
			Lasers[i].angleEaseType = angleEaseType;
			Lasers[i].angleEaseTime = angleEaseTime;
			Lasers[i].startSpeed = startSpeed;
			Lasers[i].endSpeed = endSpeed;
			Lasers[i].speedEaseType = speedEaseType;
			Lasers[i].speedEaseTime = speedEaseTime;
			Lasers[i].popFrame = frame;
			Lasers[i].length = length;
			Lasers[i].width = width;
			Lasers[i].frontNode = 0;
			Lasers[i].currentNodeNum = 0;
			Lasers[i].isHead = 0;
			Lasers[i].ID = 0;
			Lasers[i].params = params;
			return;
		}
	}
	if (aim == 1) {
		Lasers.emplace_back(1, isCol, pos, Plyr.AimPlayer(pos) + startAngle, Plyr.AimPlayer(pos) + endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, length, width, ID, params);
	}
	else {
		Lasers.emplace_back(1, isCol, pos, startAngle, endAngle, angleEaseType, angleEaseTime, 0, 0, 0, 0, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, frame, length, width, ID, params);
	}
}

void
CreateLaserGroup(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int way, double spread, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 1, spread / way * i + startAngle + spread / (way * 2) - spread / 2, spread / way * i + endAngle + spread / (way * 2) - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, isCol, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, 0, spread / way * i + startAngle - spread / 2, spread / way * i + endAngle - spread / 2, angleEaseType, angleEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, ID, params);
		}
		break;
	}
}

void
CreateSimpleLaserGroup(Vec2D pos, double length, double width, Color color, int style, int blend, int pal, double colSize, double size, int way, double spread, int aim, double angle, double speed, int ID, const std::vector<std::any>& params) {
	switch (aim) {
	case 0:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 1:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 0, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	case 2:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 1, spread / way * i + angle + spread / (way * 2) - spread / 2, spread / way * i + angle + spread / (way * 2) - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	default:
		for (int i = 0; i < way; i++) {
			CreateLaser(pos, length, width, color, style, blend, pal, 1, colSize, colSize, 0, 0, size, size, 0, 0, 0, spread / way * i + angle - spread / 2, spread / way * i + angle - spread / 2, 0, 0, speed, speed, 0, 0, ID, params);
		}
		break;
	}
}

void
MoveLasers() {
	for (Laser& L : Lasers) {
		L.UpdateObject();
		L.ShowLaser();
	}
	if (frame % 10 == 0) {
		std::sort(Lasers.begin(), Lasers.end(), [](const Laser& a, const Laser& b) {
			return a.popFrame < b.popFrame;
			});
		for (int i = 0; i < Lasers.size(); i++) {
			if (Lasers[i].alive == 0) {
				Lasers.erase(Lasers.begin() + i);
			}
		}
	}
}