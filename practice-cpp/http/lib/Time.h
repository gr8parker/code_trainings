#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <string>

inline std::string getCurrentTime() {
    time_t rawtime;
    struct tm * timeinfo;
    char ctime[80];
    time( &rawtime);
    timeinfo = localtime( &rawtime);
    strftime(ctime, 80, "%x %X", timeinfo);
    std::string str;
    str = ctime;
    return str;
}


#endif /* TIME_H */
