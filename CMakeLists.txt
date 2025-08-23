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
    src/protocol.h
    src/io_utils.h
    src/usb_utils.h
    # Sources
    src/config.c
    src/main.c
    src/io_utils.c
    src/usb_utils.c
)

# Add src to include path so tusb_config.h is found among other reasons.
target_include_directories(tb6600_controller PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
)

set_target_properties(tb6600_controller PROPERTIES
    EXPORT_COMPILE_COMMANDS ON
)

# Use C17
target_compile_features(tb6600_controller PUBLIC c_std_17)

# Enable uart output for debugging
pico_enable_stdio_usb(tb6600_controller 0)
pico_enable_stdio_uart(tb6600_controller 1)

pico_add_extra_outputs(tb6600_controller)

target_link_libraries(tb6600_controller PUBLIC
    pico_stdlib hardware_pwm hardware_gpio hardware_i2c hardware_timer tinyusb_device
)
