#ifndef LOGGER_H
#define LOGGER_H

#include <syslog.h>
#include <string>

using namespace std;

class Logger
{
public:
    Logger();
    ~Logger();
    void log(string topic, string message);
};

#endif // LOGGER_H
