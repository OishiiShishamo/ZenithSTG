#include "main.h"

#include "object.h"
#include "player.h"

void
Object::UpdateObject() {
	if (!(flags & kIsAlive)) return;

	UpdateEase();

	vec = AngleToVec2D(angle);
	GrazeObject();
	MoveFunc();
}

void
Object::UpdateEase() {
	double elapsed_frame = (static_cast<double>(t - pop_t));
	if (angle_ease_time == 0) {
		angle = end_angle;
	}
	else {
		angle_t = elapsed_frame / angle_ease_time;
		if (angle_t > 1)angle_t = 1;
		angle = Easing(angle_ease_type, angle_t, start_angle, end_angle);
	}
	if (is_aligned_angle == 1) {
		show_angle = angle;
	}

	if (speed_ease_time == 0) {
		speed = end_speed;
	}
	else {
		speed_t = elapsed_frame / speed_ease_time;
		if (speed_t > 1) speed_t = 1;
		speed = Easing(speed_ease_type, speed_t, start_speed, end_speed);
	}

	if (col_size_ease_time == 0) {
		col_size = end_col_size;
	}
	else {
		col_tize_t = elapsed_frame / col_size_ease_time;
		if (col_tize_t > 1)col_tize_t = 1;
		col_size = Easing(col_size_ease_type, col_tize_t, start_col_size, end_col_size);
	}

	if (size_ease_time == 0) {
		size = end_size;
	}
	else {
		size_t = elapsed_frame / size_ease_time;
		if (size_t > 1) size_t = 1;
		size = Easing(size_ease_type, size_t, start_size, end_size);
	}
}

void
Object::MoveObject(double speed) {
	pos += vec * speed;
}

int
Object::ColliCheckObject() {
	return 0;
}

void
Object::GrazeObject() {
}

int
Object::CheckPosBounds() {
	return 0;
}

int
Object::CheckCollisionAndBounds() {
	if (flags & kIsCol) {
		if (ColliCheckObject()) {
			flags &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		flags &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
Object::MoveFunc() {
	switch (id) {
	case 0:
	default: {
		int needsMultiStep = speed >= col_size + Plyr.col_size && flags & kIsCol;
		if (needsMultiStep) {
			int step = static_cast<int>(std::ceil(speed / 1.0f));
			for (int i = 0; i < step; i++) {
				MoveObject(speed / step);
				if (flags & kIsCol) {
					ColliCheckObject();
				}
				if (CheckPosBounds()) {
					flags &= ~kIsAlive;
					break;
				}
			}
		}
		else {
			MoveObject(speed);
			if (flags & kIsCol) {
				ColliCheckObject();
			}
			if (CheckPosBounds()) flags &= ~kIsAlive;
		}
	}
	}
}
