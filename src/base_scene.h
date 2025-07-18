#pragma once
#ifndef ZENITHSTG_SRC_BASESCENE_H_
#define ZENITHSTG_SRC_BASESCENE_H_

namespace zenithstg {
	class BaseScene {
	public:
		virtual void Update() = 0;
		virtual ~BaseScene() = default;
	private:
	};
}

#endif  // ZENITHSTG_SRC_BASESCENE_H_