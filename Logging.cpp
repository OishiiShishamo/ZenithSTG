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
Logger(std::string logString, int logType) {
	switch (logType) {
	case LOG_INFO:
		addLog("[INFO]: " + logString);
		break;
	case LOG_WARNING:
		addLog("[WARN]: " + logString);
		break;
	case LOG_ERROR:
		addLog("[ERR]: " + logString);
		break;
	case LOG_DEBUG:
		addLog("[DEBUG]: " + logString);
		break;
	default:
		addLog("[INFO]: " + logString);
		break;
	}
}