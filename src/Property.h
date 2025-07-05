#pragma once
#ifndef ZENITHSTG_SRC_PROPERTY_H_
#define ZENITHSTG_SRC_PROPERTY_H_

class Property {
public:
	std::string title = "ZenithSTG";
	int window_size = 2;
	int is_window = 1;
	std::atomic<long long> hi_score = 0;
	int bgm_volume = 100;
	int se_volume = 80;
};

#endif