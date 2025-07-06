#include "score.h"

#include <atomic>

#include "property.h"

void
AddScore(long long num) {
	score += num;
	if (score > properties_.hi_score_) properties_.hi_score_ = score.load();
}

void
SetScore(long long num) {
	score = num;
	if (score > properties_.hi_score_) properties_.hi_score_ = score.load();
}