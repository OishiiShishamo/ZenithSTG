#pragma once
#ifndef PROPERTY_H
#define PROPERTY_H

class Property {
public:
	std::string title = "ZenithSTG";
	int windowSize = 2;
	int isWindow = 1;
	std::atomic<long long> hiScore = 0;
	int BGMVolume = 100;
	int SEVolume = 80;
};

#endif