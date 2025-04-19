#include "Main.h"

#include "Easing.h"
#include "Object.h"
#include "Player.h"

void
Object::UpdateObject(long long Index) {
	if (!(flags & ALIVE)) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	MoveFunc();
}

void
Object::UpdateEase() {
	double elapsedFrame = (static_cast<double>(frame - popFrame));
	if (angleEaseTime == 0) {
		angle = endAngle;
	}
	else {
		angleT = elapsedFrame / angleEaseTime;
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
		speedT = elapsedFrame / speedEaseTime;
		if (speedT > 1) speedT = 1;
		speed = Easing(speedEaseType, speedT, startSpeed, endSpeed);
	}

	if (colSizeEaseTime == 0) {
		colSize = endColSize;
	}
	else {
		colSizeT = elapsedFrame / colSizeEaseTime;
		if (colSizeT > 1)colSizeT = 1;
		colSize = Easing(colSizeEaseType, colSizeT, startColSize, endColSize);
	}

	if (sizeEaseTime == 0) {
		size = endSize;
	}
	else {
		sizeT = elapsedFrame / sizeEaseTime;
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
}

int
Object::CheckPosBounds() {
	return 0;
}

int
Object::CheckCollisionAndBounds() {
	if (flags & IS_COL) {
		ColliCheckObject();
	}
	if (CheckPosBounds()) {
		flags ^= ALIVE;
		return 1;
	}
	return 0;
}

void
Object::MoveFunc() {
	switch (ID) {
	case 0:
	default: {
		int needsMultiStep = speed >= colSize + Plyr.colSize && flags & IS_COL;
		if (needsMultiStep) {
			int step = static_cast<int>(std::ceil(speed / 1.0f));
			for (int i = 0; i < step; i++) {
				MoveObject(speed / step);
				if (flags & IS_COL) {
					ColliCheckObject();
				}
				if (CheckPosBounds()) {
					flags ^= ALIVE;
					break;
				}
			}
		}
		else {
			MoveObject(speed);
			if (flags & IS_COL) {
				ColliCheckObject();
			}
			if (CheckPosBounds()) flags ^= ALIVE;
		}
	}
	}
}
