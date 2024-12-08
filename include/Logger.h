#ifndef LOGGER_H
#define LOGGER_H

using namespace std;

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
  // Add a mode parameter to specify append or overwrite
  Logger(const string &filename, bool append = true) {
    ios_base::openmode mode = append ? ios::app : ios::trunc;
    logFile.open(filename, mode);

    if (!logFile.is_open()) {
      cerr << "Error opening log file." << endl;
    }
  }

  ~Logger() { logFile.close(); }

  void log(LogLevel level, const string &message) {
    time_t now = time(0);
    tm *timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    ostringstream logEntry;
    logEntry << "[" << timestamp << "] " << levelToString(level) << ": "
             << message << endl;

    cout << logEntry.str();

    if (logFile.is_open()) {
      logFile << logEntry.str();
      logFile.flush();
    }
  }

private:
  ofstream logFile;

  string levelToString(LogLevel level) {
    switch (level) {
    case DEBUG:
      return "DEBUG";
    case INFO:
      return "INFO";
    case WARNING:
      return "WARNING";
    case ERROR:
      return "ERROR";
    case CRITICAL:
      return "CRITICAL";
    default:
      return "UNKNOWN";
    }
  }
};

void Log(std::string message, LogLevel level = LogLevel::DEBUG,
         std::string filename = "log.txt", bool append = true);

#endif
