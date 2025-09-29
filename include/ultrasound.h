#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <msp430.h>
#include <stdbool.h>

#include "util.h"

#define TRIG_PIN BIT1
#define ECHO_PIN BIT2

#define ULTRASONIC_DIR_REG P1DIR
#define ULTRASONIC_REN_REG P1REN
#define ULTRASONIC_OUT_REG P1OUT
#define ULTRASONIC_IN_REG P1IN
#define ULTRASONIC_DELAY 10

#define SPEED_SOUND 343.0f
#define MAXIMUM_DISTANCE 0.2f

void initTimerUltrasound();
void initUltrasoundGPIO();

void setTimer(bool enable);
float getDistance();
void setTrig(bool enable);

#endif
