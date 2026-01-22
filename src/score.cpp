#include "score.h"

#include <atomic>

#include "property.h"

namespace zenithstg {
	void AddScore(long long num) {
		score += num;
		if (score > properties_.hi_score_) properties_.hi_score_.store(score.load());
	}

	void SetScore(long long num) {
		score = num;
		if (score > properties_.hi_score_) properties_.hi_score_.store(score.load());
	}
}