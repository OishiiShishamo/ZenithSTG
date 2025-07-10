#include "background.h"

#include "DxLib.h"

#include "color.h"

namespace zenithstg {
	void Background::DrawBackground() {
		switch (id) {
		default:
			DrawBox(0, 0, 1920, 1080, GetColor(kColorGray), 1);
			break;
		}
	}

	Background bg_;
}