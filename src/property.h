#pragma once
#ifndef ZENITHSTG_SRC_PROPERTY_H_
#define ZENITHSTG_SRC_PROPERTY_H_

class Property {
public:
	std::string title_ = "ZenithSTG";
	int window_size_ = 2;
	int is_window_ = 1;
	std::atomic<long long> hi_score_ = 0;
	int bgm_volume_ = 100;
	int se_volume_ = 80;
	Property() = default;
};

#endif