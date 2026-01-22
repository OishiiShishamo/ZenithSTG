#include "lua_mng.h"

#include <sol.hpp>

#include "bullet.h"
#include "easing.h"
#include "enemy.h"
#include "laser.h"
#include "math_tool.h"
#include "particle.h"
#include "player.h"
#include "sound.h"

namespace zenithstg {
	void LuaInit(sol::state& lua) {
		lua.open_libraries(sol::lib::base, sol::lib::package);
		
		LuaBulletInit(lua);
		LuaEasingInit(lua);
		LuaEnemyInit(lua);
		LuaLaserInit(lua);
		LuaMathInit(lua);
		LuaParticleInit(lua);
		//LuaPlayerInit(lua);
		LuaSoundInit(lua);
	}
}