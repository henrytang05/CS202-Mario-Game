#include "Logger.h"

void Log(std::string message, LogLevel level, std::string filename,
         bool append) {
  static Logger logger(filename, append);
  logger.log(level, message);
}
