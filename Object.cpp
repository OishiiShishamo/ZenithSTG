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
		if (isAlignedAngle == 1) {
			showAngle = angle;
		}

		speedT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / speedEaseTime * 1.0f;
		if (speedT > 1) speedT = 1;
		speed = Easing(speedEaseType, speedT, startSpeed, endSpeed);

		colSizeT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / colSizeEaseTime * 1.0f;
		if (colSizeT > 1)colSizeT = 1;
		colSize = Easing(colSizeEaseType, colSizeT, startColSize, endColSize) * 1.0f;

		sizeT = (frame * 1.0f - popFrame * 1.0f) * 1.0f / sizeEaseTime * 1.0f;
		if (sizeT > 1) sizeT = 1;
		size = Easing(sizeEaseType, sizeT, startSize, endSize) * 1.0f;

		vecX = cos(angle);
		vecY = -sin(angle);
		if (speed >= Plyr.colSize + Plyr.colSize && isCol == 1) {
			for (int i = 0; i < std::ceil(Plyr.colSize * 1.0f / speed * 1.0f); i++) {
				posX += vecX * speed / std::ceil(Plyr.colSize / speed) * 1.0f;
				posY += vecY * speed / std::ceil(Plyr.colSize / speed) * 1.0f;
				if (Plyr.RangePlayer(posX, posY) < colSize + Plyr.colSize && isCol == 1) {
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
			if (Plyr.RangePlayer(posX, posY) < colSize + Plyr.colSize && isCol == 1) {
				Plyr.HitPlayer();
				alive = 0;
			}
			if (posX < BORDER_LEFT - 64.0f * size) alive = 0;
			if (posX > BORDER_RIGHT + 64.0f * size) alive = 0;
			if (posY < BORDER_UP - 64.0f * size) alive = 0;
			if (posY > BORDER_DOWN + 64.0f * size) alive = 0;
		}
	}
}