#include "ultrasound.h"

void initTimerUltrasound() {
  TA0CTL = TASSEL_2 | MC_0 | TACLR; // SMCLK, stop, clear
}

void initUltrasoundGPIO() {
  // Trigger output
  ULTRASONIC_DIR_REG |= TRIG_PIN;
  ULTRASONIC_OUT_REG &= ~TRIG_PIN;

  // Echo input
  ULTRASONIC_DIR_REG &= ~ECHO_PIN;
}

void setTrig(bool enable) {
  if (enable) {
    ULTRASONIC_OUT_REG |= TRIG_PIN;
  } else {
    ULTRASONIC_OUT_REG &= ~TRIG_PIN;
  }
}

void setTimer(bool enable) {
  if (enable) {
    TA0CTL |= MC_2 | TACLR;
  } else {
    TA0CTL &= ~MC_3;
  }
}

float getDistance() {
  // Send pulse
  setTrig(true);
  delay_ms(ULTRASONIC_DELAY);
  setTrig(false);

  // Wait for echo high
  while (!(ULTRASONIC_IN_REG & ECHO_PIN))
    ;
  setTimer(true);

  // Wait for echo low
  while (ULTRASONIC_IN_REG & ECHO_PIN)
    ;
  unsigned int duration = TA0R;

  setTimer(false);

  float time_sec = duration / DEFAULT_CLK;
  float distance = (time_sec * SPEED_SOUND) / 2.0;

  return distance;
}
