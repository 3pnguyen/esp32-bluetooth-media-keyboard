#pragma once

#include "constants/instances.h"

class Incremental {
  public:
    int counter;

    Incremental(int start = 0);
    void increment(int addend = 1);
    void reset(int new_value = 0);
};

// THIS CLASS IS CURRENTLY NOT IN USE, IT HAS BECOME OBSOLETE SINCE CHANGING THE BRIGHTNESS ON THE LEDs
// might have to remove later
