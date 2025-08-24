#pragma once

#include "control_state.h"

/**
 * Setup GPIO ports before use according to {@ref STEPPER_CONFIGS} from config.h.
 */
void setupGPIO();

/**
 * Must be called periodically to read sensor information.
 */
void task_read_sensors(control_states_t *control_states);

/**
 * Writes commands in control_states to the actuators.
 */
void task_write_outputs(control_states_t *control_states);
