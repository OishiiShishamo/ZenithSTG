#include "Graze.h"
#include "Score.h"
#include "Sound.h"

void
Graze() {
	addScore(GrazeScore);
	graze++;
	soundMng.ReserveSE(SE_GRAZE);
	//GrazeEffect(Plyr.pos);
}