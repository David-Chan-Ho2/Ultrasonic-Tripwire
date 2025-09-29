#include "button.h"

volatile bool buttonPressed = false;

void initButtonGPIO() {
  // Button Init
  BUTTON_DIR_REG &= ~BUTTON_PIN;
  BUTTON_REN_REG |= BUTTON_PIN;
  setButton(false);

  // Button Interrupt
  BUTTON_IES_REG |= BUTTON_PIN;
  BUTTON_IE_REG |= BUTTON_PIN;
}

void setButton(bool enable) {
  if (enable) {
    buttonPressed = true;
  } else {
    buttonPressed = false;
  }
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
