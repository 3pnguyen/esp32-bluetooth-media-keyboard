#pragma once

class Incremental {
  public:
    int counter;

    Incremental(int start = 0);
    void increment(int addend = 1);
    void reset(int new_value = 0);
};

// ----------------------------------------------------- Objects -----------------------------------------------------

extern Incremental indicator_led_incremental;
