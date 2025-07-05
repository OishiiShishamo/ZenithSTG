#include "Graze.h"
#include "Score.h"
#include "Sound.h"
#include "Particle.h"
#include "Player.h"

void
Graze() {
	AddScore(kGrazeScore);
	graze++;
	sound_mng_.ReserveSe(kSoundEffectGraze);
	GrazeParticle(Plyr.pos);
}