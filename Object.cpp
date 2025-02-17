#include "Main.h"

#include "Object.h"
#include "Player.h"
#include "Easing.h"

void
Object::MoveObject() {
	if (alive == 1) {
		angleT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / angleEaseTime * 1.0f;
		if (angleT > 1)angleT = 1;
		angle = Easing(angleEaseType, angleT, startAngle, endAngle) * 1.0f;
		if (angleEaseTime == 0) {
			angle = endAngle * 1.0f;
		}
		if (isAlignedAngle == 1) {
			showAngle = angle;
		}

		speedT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / speedEaseTime * 1.0f;
		if (speedT > 1) speedT = 1;
		speed = Easing(speedEaseType, speedT, startSpeed, endSpeed);
		if (speedEaseTime == 0) {
			speed = endSpeed * 1.0f;
		}

		colSizeT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / colSizeEaseTime * 1.0f;
		if (colSizeT > 1)colSizeT = 1;
		colSize = Easing(colSizeEaseType, colSizeT, startColSize, endColSize) * 1.0f;
		if (colSizeEaseTime == 0) {
			colSize = endColSize * 1.0f;
		}

		sizeT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / sizeEaseTime * 1.0f;
		if (sizeT > 1) sizeT = 1;
		size = Easing(sizeEaseType, sizeT, startSize, endSize) * 1.0f;
		if (sizeEaseTime == 0) {
			size = endSize * 1.0f;
		}

		vec.x = cos(angle);
		vec.y = -sin(angle);
		if (speed >= Plyr.colSize + Plyr.colSize && isCol == 1) {
			for (int i = 0; i < std::ceil(Plyr.colSize * 1.0f / speed * 1.0f); i++) {
				pos.x += vec.x * speed / std::ceil(Plyr.colSize / speed) * 1.0f;
				pos.y += vec.y * speed / std::ceil(Plyr.colSize / speed) * 1.0f;
				if (isCol == 1) {
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
							Vec2D(pos.x + cos(angle + PI / 2) * width / 2, pos.y - sin(angle + PI / 2) * width / 2),
							Vec2D(pos.x + cos(angle + PI / 2) * width / 2 + cos(angle) * length, pos.y - sin(angle + PI / 2) * width / 2 - sin(angle) * length),
							Vec2D(pos.x - cos(angle + PI / 2) * width / 2 + cos(angle) * length, pos.y + sin(angle + PI / 2) * width / 2 - sin(angle) * length),
							Vec2D(pos.x - cos(angle + PI / 2) * width / 2, pos.y + sin(angle + PI / 2) * width / 2))) {
							Plyr.HitPlayer();
							alive = 0;
						}
						break;
					default:
						break;
					}
				}
				if (pos.x < BORDER_LEFT - 64.0f * size * 4) alive = 0;
				if (pos.x > BORDER_RIGHT + 64.0f * size * 4) alive = 0;
				if (pos.y < BORDER_UP - 64.0f * size * 4) alive = 0;
				if (pos.y > BORDER_DOWN + 64.0f * size * 4) alive = 0;
			}
		}
		else {
			pos.x += vec.x * speed * 1.0f;
			pos.y += vec.y * speed * 1.0f;
			if (isCol == 1) {
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
						Vec2D(pos.x + cos(angle + PI / 2) * width / 2, pos.y - sin(angle + PI / 2) * width / 2),
						Vec2D(pos.x + cos(angle + PI / 2) * width / 2 + cos(angle) * length, pos.y - sin(angle + PI / 2) * width / 2 - sin(angle) * length),
						Vec2D(pos.x - cos(angle + PI / 2) * width / 2 + cos(angle) * length, pos.y + sin(angle + PI / 2) * width / 2 - sin(angle) * length),
						Vec2D(pos.x - cos(angle + PI / 2) * width / 2, pos.y + sin(angle + PI / 2) * width / 2))) {
						Plyr.HitPlayer();
						alive = 0;
					}
					break;
				default:
					break;
				}

			}
			if (pos.x < BORDER_LEFT - 64.0f * size * 4) alive = 0;
			if (pos.x > BORDER_RIGHT + 64.0f * size * 4) alive = 0;
			if (pos.y < BORDER_UP - 64.0f * size * 4) alive = 0;
			if (pos.y > BORDER_DOWN + 64.0f * size * 4) alive = 0;
		}
	}
}