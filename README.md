# Dependencies

* A gcc compiler chain for the triple arm-none-eabi
* newlib for arm-none-eabi. Otherwise you will encounter an error `fatal error: cannot read spec file 'nosys.specs': No such file or directory`

# Protocol

When attaching the raspberry pi pico, it will appear as a USB serial device, e.g. `/dev/ttyACM0`. The stepper can then be controlled by writing directly to the character device using a simple binary protocol. We will refer to the device talking to the RPi Pico as the *host* and to the RPi Pico as the *device*.

## Host-to-device

The host first has to write an 8-bit unsigned command id for the command it wants to execute:

| Command id | Command           |
| ---------- | ----------------- |
| 0          | Enable stepper    |
| 1          | Disable stepper   |
| 2          | Set goal position |

Then, the host needs to immediately transmit associated data for the command:

### Enable stepper

The host needs to transmit the following data sequentially:

| Data type | Semantics               |
| --------- | ----------------------- |
| uint8_t   | ID of stepper to enable |


### Enable stepper

The host needs to transmit the following data sequentially:

| Data type | Semantics                |
| --------- | ------------------------ |
| uint8_t   | ID of stepper to disable |

### Set goal position

The host needs to transmit the following data sequentially:

| Data type | Semantics                                 |
| --------- | ----------------------------------------- |
| uint8_t   | ID of stepper to set goal for             |
| uint32_t  | Goal position in degrees as signed Q16.16 |

## Device-to-host

The device will send the following data for each configured stepper to the host at 100Hz sequentially:

| Data type | Semantics                                            |
| --------- | ---------------------------------------------------- |
| uint8_t   | Stepper ID                                           |
| uint32_t  | Current stepper position in degrees as signed Q16.16 |
