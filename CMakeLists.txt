cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_PLATFORM rp2040)
set(PICO_BOARD pico)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

# We don't have C++ code but not enabling CXX will get you an
# Missing variable CMAKE_CXX_COMPILE_OBJECT error
project(my_project C CXX)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(tb6600_controller
    # Headers
    src/config.h
    src/io_utils.h
    # Sources
    src/main.c
    src/io_utils.c
)

set_target_properties(tb6600_controller PROPERTIES
    EXPORT_COMPILE_COMMANDS ON
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(tb6600_controller 1)
pico_enable_stdio_uart(tb6600_controller 0)

pico_add_extra_outputs(tb6600_controller)

target_link_libraries(tb6600_controller pico_stdlib hardware_pwm)
