#ifndef SMARTPIANO_LEDCOMMAND_H_
#define SMARTPIANO_LEDCOMMAND_H_

#include <stdint.h>

namespace SmartPiano
{

struct LedCommand
{
    uint8_t index;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;
};

}

#endif  // SMARTPIANO_LEDCOMMAND_H_