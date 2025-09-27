/**
    Name: David Ho
    Date: 7/8/25
    Assignment: Lab 4
    Youtube:
    This Program:
*/
#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include "speaker.h"
#include "ultrasound.h"
#include "button.h"

#define DEFAULT_CLK 1000000.0f

typedef enum { IDLE, ARMED, ALERT, MAX_STATES } state_t;

volatile bool buttonPressed = false;

// Init
void initGPIO();
void initTimerUltrasound();
void initTimerSpeaker();

void init();

// Speaker
void setSpeaker(bool enable);

// Button
void setButton(bool enable);

// Ultrasonic
void setTrig(bool enable);

// State functions
state_t runIdleState();
state_t runArmedState();
state_t runAlertState();

float getDistance();

void delay_ms(uint64_t milliseconds);

state_t (*state_table[MAX_STATES])() = {runIdleState, runArmedState,
                                        runAlertState};

void main() {
  state_t currentState = IDLE;
  state_t nextState = currentState;

  init();

  while (true) {
    if (currentState < MAX_STATES)
      nextState = state_table[currentState]();

    currentState = nextState;

    delay_ms(100);
  }
}

void initGPIO() {
  // Speaker Init
  SPEAKER_DIR_REG |= SPEAKER_PIN;
  SPEAKER_SEL_REG &= ~SPEAKER_PIN;

  // Button Init
  BUTTON_DIR_REG &= ~BUTTON_PIN;
  BUTTON_REN_REG |= BUTTON_PIN;
  setButton(false);

  // Button Interrupt
  BUTTON_IES_REG |= BUTTON_PIN;
  BUTTON_IE_REG |= BUTTON_PIN;

  // Trigger output
  ULTRASONIC_DIR_REG |= TRIG_PIN;
  ULTRASONIC_OUT_REG &= ~TRIG_PIN;

  // Echo input
  ULTRASONIC_DIR_REG &= ~ECHO_PIN;

  __enable_interrupt();
}

void initTimerUltrasound() {
  TA0CTL = TASSEL_2 | MC_0 | TACLR; // SMCLK, stop, clear
}

void initTimerSpeaker() {
  TA1CCR0 = 250;            // Toggle every 250 cycles = 2kHz
  TA1CCTL0 = CCIE;          // Enable interrupt
  TA1CTL = TASSEL_2 | MC_1; // SMCLK, up mode
}

void init() {
  WDTCTL = WDTPW + WDTHOLD;

  initTimerUltrasound();
  initTimerSpeaker();
  initGPIO();
}

void delay_ms(uint64_t milliseconds) {
  static const uint64_t CYCLES_PER_MS = DEFAULT_CLK / 1000;
  uint16_t i;

  for (i = 0; i < milliseconds; i++) {
    __delay_cycles(CYCLES_PER_MS);
  }
}

void setButton(bool enable) {
  if (enable) {
    buttonPressed = true;
  } else {
    buttonPressed = false;
  }
}

void setSpeaker(bool enable) {
  if (enable) {
    TA1CTL = TASSEL_2 | MC_1;
  } else {
    TA1CTL = MC_0;
    SPEAKER_OUT_REG &= ~SPEAKER_PIN;
  }
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

state_t runIdleState() {
  state_t nextState = IDLE;

  setSpeaker(false);

  if (buttonPressed) {
    setButton(false);
    nextState = ARMED;
  }

  return nextState;
}

state_t runArmedState() {
  state_t nextState = ARMED;

  float distance = getDistance();

  if (distance < MAXIMUM_DISTANCE) {
    nextState = ALERT;
  }

  return nextState;
}

state_t runAlertState() {
  state_t nextState = ALERT;

  setSpeaker(true);

  if (buttonPressed) {
    setButton(false);
    nextState = IDLE;
  }

  return nextState;
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

// Button Interrupt
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR() {
  delay_ms(BUTTON_DEBOUNCE);

  if ((BUTTON_IN_REG & BUTTON_PIN) == 0) {
    setButton(true);
  }

  BUTTON_IFG_REG &= ~BUTTON_PIN;
}

// Speaker Interrupt
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void) {
  SPEAKER_OUT_REG ^= SPEAKER_PIN; // Toggle P2.1 using exclusive-OR
}
