#include "io_utils.h"
#include "usb_utils.h"
#include <pico/stdlib.h>
#include <hardware/timer.h>
#include <stdio.h>
#include "config.h"

bool setup() {
    // Initialize stdio
    if (!stdio_init_all()) {
        return false;
    }
    // Initialize GPIO pins
    setupGPIO();
    // Initialize USB
    if (!setupUSB()) {
        return false;
    }

    return 0;
}

/**
 * Interval of the control loop in microseconds
 */
const unsigned int CONTROL_LOOP_INTERVAL_US = 1000000 / CONTROL_LOOP_HZ;

bool loop_process() {
}

int main(int argc, char **argv) {
    bool err;
    // Setup ports etc.
    err = setup();
    if (err != 0) {
        printf("Setup failed. Error %i", err);
        return 1;
    }

    // Main loop
    while (true) {
        // Get the time we began processing the control loop, to calculate
        // processing duration later.
        const uint64_t loop_begin_us = time_us_64();
        // Process the control loop
        loop_process();
        // Get duration that control loop took
        const uint64_t loop_duration = time_us_64() - loop_begin_us;
        // Sleep for CONTROL_LOOP_INTERVAL_US excl. loop process duration
        sleep_us(CONTROL_LOOP_INTERVAL_US - loop_duration);
    }
}
