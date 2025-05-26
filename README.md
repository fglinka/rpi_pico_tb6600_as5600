# Dependencies

* A gcc compiler chain for the triple arm-none-eabi
* newlib for arm-none-eabi. Otherwise you will encounter an error `fatal error: cannot read spec file 'nosys.specs': No such file or directory`

# Protocol

When attaching the raspberry pi pico, it will appear as a USB serial device, e.g. `/dev/ttyACM0`. The stepper can then be controlled by writing directly to the character device using a simple binary protocol. We will refer to the device talking to the RPi Pico as the *host* and to the RPi Pico as the *device*. There are `HostPacket`s which are sent from host to device and `DevicePacket`s which are sent from device to host. All packets are 8 bytes (64 bit) long and padded if their content is shorter to make handling easier. Numbers of greater than 1 byte are always little endian. For a overview of the protocol, see [the protocol.h header](./src/protocol.h).
