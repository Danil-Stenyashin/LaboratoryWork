#ifndef LOGS_H
#define LOGS_H

#include <string>

class Logs {
public:
    void initializeLogFile();
    void logEvent(const std::string& event);
};

#endif
