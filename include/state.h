#ifndef STATE_H
#define STATE_H

#include "button.h"
#include "speaker.h"
#include "ultrasound.h"

typedef enum { IDLE, ARMED, ALERT, MAX_STATES } state_t;

state_t runState(state_t current);

state_t runIdleState();
state_t runArmedState();
state_t runAlertState();

#endif
