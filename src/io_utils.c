#include "io_utils.h"

#include "config.h"
#include <pico/stdlib.h>
#include <hardware/pwm.h>

/**
 * Setup the PWM port(s). Basically only the pulse output
 */
void setupPWMPorts(const struct StepperConfig *config) {
    // Get the slice and channel the pulse pin is connected to
    unsigned int pulse_slice = pwm_gpio_to_slice_num(config->pin_pulse);
    unsigned int pulse_channel = pwm_gpio_to_channel(config->pin_pulse);
    // Set pin to pwm
    gpio_set_function(config->pin_pulse, GPIO_FUNC_PWM);
    // We emit a signal with a duty cycle of 1/4
    pwm_set_wrap(pulse_slice, 3);
    switch (config->connection_type) {
        case COMMON_ANODE:
            // This means low activates pulse, so we emit 3/4 of high signal
            pwm_set_chan_level(pulse_slice, pulse_channel, 3);
            break;
        case COMMON_CATHODE:
            // This means high activates pulse, so we emit 1/4 of high signal
            pwm_set_chan_level(pulse_slice, pulse_channel, 1);
            break;
    }
}

/**
 * Setup general GPIO ports (i.e. non-pwm or i2c pins).
 */
void setupGeneralPorts(const struct StepperConfig *config) {
}

/**
 * Setup GPIO ports used for I2c
 */
void setupI2cPorts(const struct StepperConfig *config) {
}

void setupPorts() {

    for (size_t stepper_id = 0; stepper_id < NUM_STEPPERS; ++stepper_id) {
        // Get pointer to config
        const struct StepperConfig *config = &STEPPER_CONFIGS[stepper_id];
        // Setup general GPIO ports
        setupGeneralPorts(config);
        // Setup the pwm ports
        setupPWMPorts(config);
        // Setup the i2c ports
        setupI2cPorts(config);
    }
}
