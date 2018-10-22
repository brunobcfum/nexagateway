#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::log(string topic, string message){
    openlog(topic.c_str(), LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_MAKEPRI(LOG_USER, LOG_INFO), message.c_str());
    closelog();
}

