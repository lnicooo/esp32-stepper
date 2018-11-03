#include <stdint.h>
#include <stdbool.h>

#define CW 1
#define CCW 0

struct stepper_pins{
    uint8_t pin1;
    uint8_t pin2;
    uint8_t pin3;
    uint8_t pin4;
};

void stepper_init(struct stepper_pins *stepper_ptr);

void step(struct stepper_pins *stepper_ptr, int step);

void full_steps(struct stepper_pins *stepper_ptr,int steps, bool dir);

