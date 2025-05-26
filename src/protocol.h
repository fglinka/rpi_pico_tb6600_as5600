/*
 * protocol.h header for rpi_tb6600_as5600
 * In contrast to the rest of the application this header is licensed under MIT to ease
 * writing host code in non-GPL'd software. 
 *
 * Copyright © 2025 Felix Glinka
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <stdint.h>

const uint8_t HP_ID_ENABLE_STEPPER = 0; ///< Used for {@ref HostPacketEnableStepper}.
const uint8_t HP_ID_DISABLE_STEPPER = 1; ///< Used for {@ref HostPacketDisableStepper}.
const uint8_t HP_ID_SET_POSITION_GOAL = 2; ///< Set the position goal for a stepper.

/**
 * Requests are always sent from the host to the device. Always 64 bits (8 bytes) long.
 */
struct __attribute__((__packed__)) HostPacket {
    uint8_t packet_id; ///< The request ID, one of the HP_ID_XXX values.
    uint8_t packet_data[7]; ///< Packet data padding, depends on request ID.
};

struct __attribute__((__packed__)) HostPacketEnableStepper {
    uint8_t packet_id; ///< HP_ID_ENABLE_STEPPER
    uint8_t stepper_id; ///< The ID of the stepper to enable.
    uint8_t pad[6]; ///< Padding
};

struct __attribute__((__packed__)) HostPacketDisableStepper {
    uint8_t packet_id; ///< HP_ID_DISABLE_STEPPER
    uint8_t stepper_id; ///< The ID of the stepper to disable.
    uint8_t pad[6]; ///< Padding
};

struct __attribute__((__packed__)) HostPacketSetPositionGoal {
    uint8_t packet_id; ///< HP_ID_SET_POSITION_GOAL
    uint8_t stepper_id; ///< The ID of the stepper to set the position goal for.
    uint16_t position_goal; ///< The position goal in degrees as fixed point signed Q16.16.
                            ///< (15 bits before, 16 after decimal point). Beware,
                            ///< has to be little endian.
    uint8_t pad[4]; ///< Padding
};

const uint8_t DP_ID_ACKNOWLEDGEMENT = 0; ///< Used for {@ref DevicePacketAcknowledgement}.
const uint8_t DP_ID_CURRENT_POSITION = 1; ///< Used for {@ref DevicePacketCurrentPosition}.

/**
 * Device packets are always sent from the device to the host. Either to periodically report
 * sensor data or to send acknowledgements for host packets. Always 64 bits (8 bytes) long.
 */
struct __attribute__((__packed__)) DevicePacket {
    uint8_t packet_id; ///< Determines which kind of Response this is. One of DP_ID_XXX.
    uint8_t packet_data[7]; ///< Padding for response content.
};

const uint8_t ACK_ID_ENABLE_STEPPER = 0; ///< Acknowledges {@HostPacketEnableStepper}.
const uint8_t ACK_ID_DISABLE_STEPPER = 1; ///< Acknowledges {@HostPacketDisableStepper}.
const uint8_t ACK_ID_SET_POSITION_GOAL = 2; ///< Acknowledges {@HostPacketSetPositionGoal}.

/**
 * Packet that acknowledges that the device has received and processed a request by the host.
 */
struct __attribute__((__packed__)) DevicePacketAcknowledgement {
    uint8_t response_id; ///< DP_ID_ACKNOWLEDGEMENT;
    uint8_t acknowledgement_id; ///< Determines what this packet Acknowledges. One of
                                ///< ACK_ID_XXX.
    uint8_t pad[6]; ///< Pad to 8 bytes.
};

struct __attribute__((__packed__)) DevicePacketCurrentPosition {
    uint8_t response_id; ///< DP_ID_ACKNOWLEDGEMENT;
    uint8_t stepper_id; ///< The ID of the stepper the position data is reported for.
    uint16_t position_goal; ///< The current position in degrees as fixed point signed Q16.16.
                            ///< (15 bits before, 16 after decimal point). Beware,
                            ///< has to be little endian.

    uint8_t pad[4]; ///< Pad to 8 bytes.
};
