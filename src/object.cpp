#include "object.h"

#include <algorithm>
#include <any>
#include <array>
#include <cmath>
#include <vector>

#include "DxLib.h"

#include "collision.h"
#include "color.h"
#include "player.h"
#include "sound.h"
#include "utility.h"
#include "vec2d.h"

void
Object::UpdateObject() {
	if (!(flags_ & kIsAlive)) return;

	UpdateEase();

	vec_ = AngleToVec2D(angle_);
	GrazeObject();
	MoveFunc();
}

void
Object::UpdateEase() {
	double elapsed_frame = (static_cast<double>(t - pop_t_));
	if (angle_ease_time_ == 0) {
		angle_ = end_angle_;
	}
	else {
		angle_t_ = elapsed_frame / angle_ease_time_;
		if (angle_t_ > 1)angle_t_ = 1;
		angle_ = Easing(angle_ease_type_, angle_t_, start_angle_, end_angle_);
	}
	if (is_aligned_angle_ == 1) {
		show_angle_ = angle_;
	}

	if (speed_ease_time_ == 0) {
		speed_ = end_speed_;
	}
	else {
		speed_t_ = elapsed_frame / speed_ease_time_;
		if (speed_t_ > 1) speed_t_ = 1;
		speed_ = Easing(speed_ease_type_, speed_t_, start_speed_, end_speed_);
	}

	if (col_size_ease_time_ == 0) {
		col_size_ = end_col_size_;
	}
	else {
		col_tize_t_ = elapsed_frame / col_size_ease_time_;
		if (col_tize_t_ > 1)col_tize_t_ = 1;
		col_size_ = Easing(col_size_ease_type_, col_tize_t_, start_col_size_, end_col_size_);
	}

	if (size_ease_time_ == 0) {
		size_ = end_size_;
	}
	else {
		size_t_ = elapsed_frame / size_ease_time_;
		if (size_t_ > 1) size_t_ = 1;
		size_ = Easing(size_ease_type_, size_t_, start_size_, end_size_);
	}
}

void
Object::MoveObject(double speed) {
	pos_ += vec_ * speed;
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
	if (flags_ & kIsCol) {
		if (ColliCheckObject()) {
			flags_ &= ~kIsAlive;
			return 1;
		}
	}
	if (CheckPosBounds()) {
		flags_ &= ~kIsAlive;
		return 1;
	}
	return 0;
}

void
Object::MoveFunc() {
	switch (id_) {
	case 0:
	default: {
		int needsMultiStep = speed_ >= col_size_ + player.col_size_ && flags_ & kIsCol;
		if (needsMultiStep) {
			int step = static_cast<int>(std::ceil(speed_ / 1.0f));
			for (int i = 0; i < step; i++) {
				MoveObject(speed_ / step);
				if (flags_ & kIsCol) {
					ColliCheckObject();
				}
				if (CheckPosBounds()) {
					flags_ &= ~kIsAlive;
					break;
				}
			}
		}
		else {
			MoveObject(speed_);
			if (flags_ & kIsCol) {
				ColliCheckObject();
			}
			if (CheckPosBounds()) flags_ &= ~kIsAlive;
		}
	}
	}
}
