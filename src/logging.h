#pragma once
#ifndef ZENITHSTG_SRC_LOGGING_H_
#define ZENITHSTG_SRC_LOGGING_H_

#include "main.h"

namespace zenithstg {
	enum class LogType {
		kLogInfo,
		kLogWarning,
		kLogError,
		kLogDebug,
	};

	void AddLogQue(std::string log);
	void WriteLog();
	void Logger(std::string log_string, LogType log_type = LogType::kLogInfo);
}

#endif