std::string debugging = "";

void
AddLogQue(std::string log) {
	debugging += log + "\n";
}

void
WriteLog() {
	std::ofstream log_file;
	log_file.open("log.txt");
	log_file << debugging;
	log_file.close();
}

void
Logger(std::string log_string, LogType log_type) {
	switch (log_type) {
	case LogType::kLogInfo:
		AddLogQue("[INFO]: " + log_string);
		break;
	case LogType::kLogWarning:
		AddLogQue("[WARN]: " + log_string);
		break;
	case LogType::kLogError:
		AddLogQue("[ERR]: " + log_string);
		break;
	case LogType::kLogDebug:
		AddLogQue("[DEBUG]: " + log_string);
		break;
	default:
		AddLogQue("[INFO]: " + log_string);
		break;
	}
}