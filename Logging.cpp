#include "Logging.h"

std::string debugging = "";

void
addLog(std::string log) {
	debugging += log + "\n";
}

void
writeLog() {
	std::ofstream logfile;
	logfile.open("log.txt");
	logfile << debugging;
	logfile.close();
}

void
Logger(std::string logString, logType logType) {
	switch (logType) {
	case logType::LOG_INFO:
		addLog("[INFO]: " + logString);
		break;
	case logType::LOG_WARNING:
		addLog("[WARN]: " + logString);
		break;
	case logType::LOG_ERROR:
		addLog("[ERR]: " + logString);
		break;
	case logType::LOG_DEBUG:
		addLog("[DEBUG]: " + logString);
		break;
	default:
		addLog("[INFO]: " + logString);
		break;
	}
}