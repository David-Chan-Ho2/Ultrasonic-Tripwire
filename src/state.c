#include "state.h"

extern volatile bool buttonPressed;

state_t (*state_table[MAX_STATES])() = {runIdleState, runArmedState,
                                        runAlertState};

state_t runState(state_t current) {
  if (current < MAX_STATES) {
    return state_table[current]();
  }
  return IDLE;
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
