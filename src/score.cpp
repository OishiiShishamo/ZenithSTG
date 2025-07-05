#include "main.h"
#include "score.h"

void
AddScore(long long num) {
	score += num;
	if (score > properties_.hi_score) properties_.hi_score = score.load();
}

void
SetScore(long long num) {
	score = num;
	if (score > properties_.hi_score) properties_.hi_score = score.load();
}