#pragma once

#include <stdint.h>
#include "config.h"

typedef struct control_state {
    int goal_position; ///< The goal position for this stepper. signed Q16.16
    int current_position; ///< Current position of this stepper, read from sensor. Signed Q16.16
} control_state_t;

typedef struct control_states {
    control_state_t control_states[NUM_STEPPERS]; ///< Control states by stepper IDs
} control_states_t;

/**
 * Create an instance of {@ref ControlStates} with {@ref NUM_STEPPERS} instances and
 * an initial default state.
 */
control_states_t* control_states_create();

/**
 * Destroy a {@ref ControlStates} instance.
 */
void control_states_destroy(control_states_t *control_states);
