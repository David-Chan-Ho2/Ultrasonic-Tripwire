#include "speaker.h"

void initTimerSpeaker() {
  TA1CCR0 = 250;            // Toggle every 250 cycles = 2kHz
  TA1CCTL0 = CCIE;          // Enable interrupt
  TA1CTL = TASSEL_2 | MC_1; // SMCLK, up mode
}

void initSpeakerGPIO() {
  SPEAKER_DIR_REG |= SPEAKER_PIN;
  SPEAKER_SEL_REG &= ~SPEAKER_PIN;
}

void setSpeaker(bool enable) {
  if (enable) {
    TA1CTL = TASSEL_2 | MC_1;
  } else {
    TA1CTL = MC_0;
    SPEAKER_OUT_REG &= ~SPEAKER_PIN;
  }
}

// Speaker Interrupt
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void) {
  SPEAKER_OUT_REG ^= SPEAKER_PIN; // Toggle P2.1 using exclusive-OR
}
