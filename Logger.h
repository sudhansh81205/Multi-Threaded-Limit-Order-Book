#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

using namespace std;

class Logger{
private:
  ofstream file;

public:

    Logger();
    ~Logger();
    void log(const string message);
};

#endif