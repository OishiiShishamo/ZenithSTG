#include "Main.h"
#include "Score.h"

void
addScore(long long num) {
	score += num;
	if (score > Properties.hiScore) Properties.hiScore = score;
}

void
setScore(long long num) {
	score = num;
	if (score > Properties.hiScore) Properties.hiScore = score;
}