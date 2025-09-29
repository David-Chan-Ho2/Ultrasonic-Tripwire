#include "util.h"

void delay_ms(uint64_t milliseconds) {
  static const uint64_t CYCLES_PER_MS = DEFAULT_CLK / 1000;
  uint16_t i;

  for (i = 0; i < milliseconds; i++) {
    __delay_cycles(CYCLES_PER_MS);
  }
}
