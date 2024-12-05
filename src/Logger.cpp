#include "Logger.h"

void Log(const char *filename, LogLevel level, std::string message) {
    Logger logger(filename);
    logger.log(level, message);
}
