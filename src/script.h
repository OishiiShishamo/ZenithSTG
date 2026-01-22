#pragma once
#ifndef ZENITHSTG_SRC_SCRIPT_H_
#define ZENITHSTG_SRC_SCRIPT_H_

#include <fstream>
#include <functional>
#include <string>

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
		void LoadScript(std::string path);
	private:
		std::function<void()> _script;
	};
}

#endif