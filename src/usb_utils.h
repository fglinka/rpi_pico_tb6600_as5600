#pragma once

/**
 * Sets up a usb device for use with the protocol.
 *
 * @return 0 if successfull, none-zero otherwise.
 */
int setupUSB();

/**
 * Must be called periodically to handle USB interrupts
 */
void taskUSB();
