#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vec.h"

typedef struct {
    Vec_t pos;
    Vec_t force;
} Ball_t;

typedef struct {
    uint8_t center;
} Paddle_t;

void setPosition(Ball_t* ball, Vec_t pos);

void update(Ball_t* ball);

#endif