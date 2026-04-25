#include "classes/Incremental.h"

Incremental::Incremental(int start) : counter(start) {}

void Incremental::increment(int addend) {counter += addend;}

void Incremental::reset(int new_value) {counter = new_value;}

// ----------------------------------------------------- Objects -----------------------------------------------------

Incremental indicator_led_incremental(0);
