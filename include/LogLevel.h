#ifndef SMARTPIANO_LOGLEVEL_H_
#define SMARTPIANO_LOGLEVEL_H_

namespace SmartPiano
{

enum LogLevel : unsigned char
{
    TEST = 1,

    ERROR = 2,

    WARNING = 4,

    INFO = 8,

    DEBUG = 16,

    NOISY = 32
};

}

#endif  // SMARTPIANO_LOGLEVEL_H_