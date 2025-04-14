#include "Main.h"

#include "Object.h"
#include "Player.h"
#include "Easing.h"

void
Object::UpdateObject(long long Index) {
	if (!alive) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	if (speed >= colSize + Plyr.colSize && isCol == 1) {
		for (int i = 0; i < static_cast<int>(std::ceil(speed / 1.0f)); i++) {
			if (objType != OBJECT_BENT_LASER || isHead == 1) {
				MoveObject(speed / static_cast<int>(std::ceil(speed / 1.0f)));
			}
			if (isCol == 1) {
				ColliCheckObject();
			}
			if (CheckOutOfScreen()) alive = 0;
		}
	}
	else {
		if (objType != OBJECT_BENT_LASER || isHead == 1) {
			MoveObject(speed);
		}
		if (isCol == 1) {
			ColliCheckObject();
		}
		if (CheckOutOfScreen()) alive = 0;
	}
}

void
Object::UpdateEase() {
	if (angleEaseTime == 0) {
		angle = endAngle;
	}
	else {
		angleT = (static_cast<double>(frame - popFrame)) / angleEaseTime;
		if (angleT > 1)angleT = 1;
		angle = Easing(angleEaseType, angleT, startAngle, endAngle);
	}
	if (isAlignedAngle == 1) {
		showAngle = angle;
	}

	if (speedEaseTime == 0) {
		speed = endSpeed;
	}
	else {
		speedT = (static_cast<double>(frame - popFrame)) / speedEaseTime;
		if (speedT > 1) speedT = 1;
		speed = Easing(speedEaseType, speedT, startSpeed, endSpeed);
	}

	if (colSizeEaseTime == 0) {
		colSize = endColSize;
	}
	else {
		colSizeT = (static_cast<double>(frame - popFrame)) / colSizeEaseTime;
		if (colSizeT > 1)colSizeT = 1;
		colSize = Easing(colSizeEaseType, colSizeT, startColSize, endColSize);
	}

	if (sizeEaseTime == 0) {
		size = endSize;
	}
	else {
		sizeT = (static_cast<double>(frame - popFrame)) / sizeEaseTime;
		if (sizeT > 1) sizeT = 1;
		size = Easing(sizeEaseType, sizeT, startSize, endSize);
	}
}

void
Object::MoveObject(double speed) {
	pos.x += vec.x * speed;
	pos.y += vec.y * speed;
}

void
Object::ColliCheckObject() {
	switch (objType) {
	case OBJECT_BULLET:
	case OBJECT_ENEMY:
		if (colCircleAndCircle(pos, Plyr.pos, colSize + Plyr.colSize)) {
			Plyr.HitPlayer();
			alive = 0;
		}
		break;
	case OBJECT_LASER:
		if (colPointAndRect(Plyr.pos,
			Vec2D(pos.x + cos(angle + PI / 2) * colSize / 2, pos.y - sin(angle + PI / 2) * colSize / 2),
			Vec2D(pos.x + cos(angle + PI / 2) * colSize / 2 + cos(angle) * length, pos.y - sin(angle + PI / 2) * colSize / 2 - sin(angle) * length),
			Vec2D(pos.x - cos(angle + PI / 2) * colSize / 2 + cos(angle) * length, pos.y + sin(angle + PI / 2) * colSize / 2 - sin(angle) * length),
			Vec2D(pos.x - cos(angle + PI / 2) * colSize / 2, pos.y + sin(angle + PI / 2) * colSize / 2))) {
			Plyr.HitPlayer();
			alive = 0;
		}
		break;
	default:
		break;
	}
}

int
Object::CheckOutOfScreen() {
	if (pos.x < BORDER_LEFT - 64.0f * size * 4) return 1;
	if (pos.x > BORDER_RIGHT + 64.0f * size * 4) return 1;
	if (pos.y < BORDER_UP - 64.0f * size * 4) return 1;
	if (pos.y > BORDER_DOWN + 64.0f * size * 4) return 1;
	return 0;
}