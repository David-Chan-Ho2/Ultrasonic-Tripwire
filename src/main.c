#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include "button.h"
#include "main.h"
#include "speaker.h"
#include "state.h"
#include "ultrasound.h"
#include "util.h"

void main() {
  state_t currentState = IDLE;
  state_t nextState = currentState;

  initTimers();
  initGPIO();

  while (true) {
    if (currentState < MAX_STATES)
      nextState = runState(currentState);

    currentState = nextState;

    delay_ms(DELAY);
  }
}

void initTimers() {
  initTimerUltrasound();
  initTimerSpeaker();
}

void initGPIO() {
  initSpeakerGPIO();
  initButtonGPIO();
  initUltrasoundGPIO();
  __enable_interrupt();
}
