#include "graze.h"

#include "particle.h"
#include "player.h"
#include "score.h"
#include "sound.h"

namespace zenithstg {
	void Graze() {
		AddScore(kGrazeScore);
		graze++;
		sound_mng_.ReserveSe(kSoundEffectGraze);
		GrazeParticle(player_.pos_);
	}
}