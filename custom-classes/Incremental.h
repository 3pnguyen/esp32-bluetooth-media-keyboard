#ifndef INCREMENTAL_H
#define INCREMENTAL_H

class Incremental {
  public:
    int counter;

    Incremental(int start = 0);
    void increment(int addend = 1);
    void reset(int new_value = 0);
};

#endif