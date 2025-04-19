#pragma once
#ifndef LOGGING_H
#define LOGGING_H

#include "Main.h"

enum logType {
	LOG_INFO = 0,
	LOG_WARNING = 1,
	LOG_ERROR = 2,
	LOG_DEBUG = 3,
};

void addLog(std::string log);
void writeLog();
void Logger(std::string logString, int logType = LOG_INFO);

#endif