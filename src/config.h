#pragma once

#include <stdint.h>

enum ConnectionType {
    COMMON_ANODE,
    COMMON_CATHODE
};

struct StepperConfig {
    // Whether the stepper is wired in common anode or cathode configuration
    enum ConnectionType connection_type;
    // The GPIO pin wired to the ENA+/- pin
    const unsigned int pin_enable;
    // The GPIO pin wired to the DIR+/- pin
    const unsigned int pin_direction;
    // The GPIO pin wired to the PUL+/- pin
    const unsigned int pin_pulse;
    // The step angle of the stepper (ignoring microstep mode) in Q16.16. Usually 360/200=1.8°.
    const uint32_t step_angle;
    // The amound of subdivision set for microstepping.
    const unsigned int step_subdivisions;
    // (Positive) velocity limit in Degrees Q16.16. Both for forward and reverse.
    const uint32_t max_velocity;
    // The i2c instance used. Either 0 or 1, must be unique per sensor.
    const uint8_t i2c_instance;
    // The GPIO pin used for the AS5600 I²C data signal
    const unsigned int pin_sensor_sda;
    // The GPIO pin used for the AS5600 I²C clock signal
    const unsigned int pin_sensor_scl;
};

const struct StepperConfig STEPPER_CONFIGS[] = {
    {COMMON_CATHODE, 0, 1, 2, (uint32_t)(1.8 * (1 << 16)), 1, (uint32_t)(20 * (1 << 16))}
};

const unsigned int NUM_STEPPERS = 1;
