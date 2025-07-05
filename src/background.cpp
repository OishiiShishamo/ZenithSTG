#include "Main.h"

#include "background.h"

void
Background::DrawBackground() {
	switch (id) {
	default:
		DrawBox(0, 0, 1920, 1080, GetColor(kColorGray), 1);
		break;
	}
}

Background BG;