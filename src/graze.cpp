#include "graze.h"
#include "score.h"
#include "sound.h"
#include "particle.h"
#include "player.h"

void
Graze() {
	AddScore(kGrazeScore);
	graze++;
	sound_mng_.ReserveSe(kSoundEffectGraze);
	GrazeParticle(Plyr.pos);
}