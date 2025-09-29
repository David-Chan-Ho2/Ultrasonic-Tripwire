#ifndef SPEAKER_H
#define SPEAKER_H

#include <msp430.h>
#include <stdbool.h>

#define BUZZ_NOTE 1976

#define SPEAKER_PIN BIT1
#define SPEAKER_DIR_REG P2DIR
#define SPEAKER_OUT_REG P2OUT
#define SPEAKER_SEL_REG P2SEL

void initTimerSpeaker();
void initSpeakerGPIO();
void setSpeaker(bool enable);

#endif
