#include "Graze.h"
#include "Score.h"
#include "Sound.h"
#include "Particle.h"
#include "Player.h"

void
Graze() {
	addScore(GrazeScore);
	graze++;
	soundMng.ReserveSE(SE_GRAZE);
	GrazeParticle(Plyr.pos);
}