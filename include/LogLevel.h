#ifndef SMARTPIANO_LOGLEVEL_H_
#define SMARTPIANO_LOGLEVEL_H_

namespace SmartPiano
{

enum LogLevel : unsigned char
{
    ERROR = 1,

    WARNING = 2,

    INFO = 4,

    DEBUG = 8,

    TEST = 16,

    NOISY = 32
};

}

#endif  // SMARTPIANO_LOGLEVEL_H_