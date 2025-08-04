#include "script.h"

#include "background.h"
#include "bullet.h"
#include "enemy.h"
#include "math_tool.h"
#include "laser.h"
#include "utility.h"

namespace zenithstg {
	std::array<Script, kStageNum> scripts;

	void Script::RunScript() {
		switch (id_) {
		case 0: {
			//TESTDANMAKUKUKUKUKUKUKUKUKUKUKU
			if (t % 1 == 0) {
				
			}
			break;
		}
		}
	}
}