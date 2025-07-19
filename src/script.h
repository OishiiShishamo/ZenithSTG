#pragma once
#ifndef ZENITHSTG_SRC_SCRIPT_H_
#define ZENITHSTG_SRC_SCRIPT_H_

#include "background.h"
#include "bullet.h"
#include "enemy.h"
#include "math_tool.h"
#include "laser.h"
#include "utility.h"

namespace zenithstg {
	class Script {
	public:
		int id_ = 0;
		void RunScript();
	private:
	};
}

#endif