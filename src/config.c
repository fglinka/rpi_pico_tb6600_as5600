#include "config.h"

const struct StepperConfig STEPPER_CONFIGS[] = {
    {COMMON_CATHODE, 0, 1, 2, (uint32_t)(1.8 * (1 << 16)), 1, (uint32_t)(20 * (1 << 16))}
};
