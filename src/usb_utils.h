#pragma once

#include <stdbool.h>

/**
 * Sets up a usb device for use with the protocol.
 *
 * @return 0 if successfull, none-zero otherwise.
 */
bool setupUSB();

/**
 * Must be called periodically to handle USB interrupts
 */
bool taskUSB();
