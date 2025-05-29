#include "usb_utils.h"
#include <tusb.h>

int setupUSB() {
    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO
    };
    // Initialize device 0
    tusb_init(0, &dev_init);
}

void taskUSB() {
    tusb_int_handler(0, true);
}
