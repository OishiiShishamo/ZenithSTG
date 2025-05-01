#pragma once
#ifndef LOGGING_H
#define LOGGING_H

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