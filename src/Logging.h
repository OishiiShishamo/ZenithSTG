#pragma once
#ifndef ZENITHSTG_SRC_LOGGING_H_
#define ZENITHSTG_SRC_LOGGING_H_

#include "Main.h"

enum class logType {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_DEBUG,
};

void addLog(std::string log);
void writeLog();
void Logger(std::string logString, logType logType = logType::LOG_INFO);

#endif