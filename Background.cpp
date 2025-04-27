#include "Main.h"

#include "Background.h"
#include "Color.h"

void
Background::DrawBackground() {
	switch (ID) {
	default:
		DrawBox(0, 0, 1920, 1080, GetColor(C_GRAY), 1);
		break;
	}
}

Background BG;