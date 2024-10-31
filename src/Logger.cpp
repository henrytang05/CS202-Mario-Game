#include "Logger.h"
void Log(const char *filename, LogLevel level, const std::string &message) {
#ifdef DEBUG
  Logger logger(filename);
  logger.log(level, message);
#endif
}
