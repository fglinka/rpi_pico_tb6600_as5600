#include "io_utils.h"

#include "config.h"
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <stdbool.h>

/**
 * Setup the PWM port(s). Basically only the pulse output
 */
void setupPWMPorts(const struct StepperConfig *config) {
    // Get the slice and channel the pulse pin is connected to
    const unsigned int pulse_slice = pwm_gpio_to_slice_num(config->pin_pulse);
    const unsigned int pulse_channel = pwm_gpio_to_channel(config->pin_pulse);
    // Set pin to pwm
    gpio_set_function(config->pin_pulse, GPIO_FUNC_PWM);
    // We emit a signal with a duty cycle of 1/4
    pwm_set_wrap(pulse_slice, 3);
    switch (config->connection_type) {
        case COMMON_ANODE:
            // This means low activates pulse, so we emit 3/4 of high signal
            pwm_set_chan_level(pulse_slice, pulse_channel, 3);
            gpio_pull_up(config->pin_pulse);
            break;
        case COMMON_CATHODE:
            // This means high activates pulse, so we emit 1/4 of high signal
            pwm_set_chan_level(pulse_slice, pulse_channel, 1);
            gpio_pull_down(config->pin_pulse);
            break;
    }
}

/**
 * Setup general GPIO ports (i.e. non-pwm or i2c pins).
 */
void setupGeneralPorts(const struct StepperConfig *config) {
    const unsigned int enable_pin = config->pin_enable;
    const unsigned int direction_pin = config->pin_direction;
    
    // Setup enable pin
    gpio_init(enable_pin);
    gpio_set_dir(enable_pin, GPIO_OUT);

    // Setup direction pin
    gpio_init(direction_pin);
    gpio_set_dir(direction_pin, GPIO_OUT);

    // Pull pins up for common anode, down for common cathode. I.e. always to inactive state.
    switch (config->connection_type) {
    case COMMON_ANODE: 
        gpio_pull_up(enable_pin);
        gpio_pull_up(direction_pin);
        break;
    case COMMON_CATHODE:
        gpio_pull_down(enable_pin);
        gpio_pull_down(direction_pin);
    };
}

const unsigned int AS5600_BAUDRATE = 100000; ///< I²C Baudrate in Hz used to communicate with AS5600.

/**
 * Setup GPIO ports used for I2c
 */
void setupI2cPorts(const struct StepperConfig *config) {
    // Use correct i2c instance
    struct i2c_inst *inst = config->i2c_instance == 0 ? i2c0 : i2c1;
    // Initialize i2c instance
    i2c_init(inst, AS5600_BAUDRATE);
    // Set pin functions
    gpio_set_function(config->pin_sensor_scl, GPIO_FUNC_I2C);
    gpio_set_function(config->pin_sensor_sda, GPIO_FUNC_I2C);
    // Pull pins up
    gpio_pull_up(config->pin_sensor_scl);
    gpio_pull_up(config->pin_sensor_sda);
}

void setupGPIO() {
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

void task_read_sensors(control_states_t *control_states) {
    // TODO stub
}

void task_write_outputs(control_states_t *control_states) {
    // TODO stub
}
