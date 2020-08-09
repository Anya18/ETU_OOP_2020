#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <QDebug>
#include <QString>
#include <fstream>
#include <ios>

class Logging
{
public:
    Logging();
    static void user_log(std::string s);
    static void hero_log(std::string s);
};

#endif // LOGGING_H
