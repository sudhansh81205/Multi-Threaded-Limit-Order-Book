#include "Logger.h"

Logger::Logger(){
    file.open("trades.log");
}

Logger::~Logger(){
    if (file.is_open())
        file.close();
}

void Logger::log(const string& message){
    file << message << endl;
}