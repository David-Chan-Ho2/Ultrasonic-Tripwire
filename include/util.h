#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_CLK 1000000.0f

void initTimerSpeaker();

void setSpeaker(bool enable);

void delay_ms(uint64_t milliseconds);

#endif
