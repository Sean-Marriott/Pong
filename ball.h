#ifndef BALL_H
#define BALL_H

#include "system.h"
#include "tinygl.h"
#include "vec.h"

typedef struct {
    tinygl_point_t point;
    Vec_t pos;
    Vec_t force;
} Ball_t;

Ball_t ball;

void ball_init(void);

void ball_display(void);

void ball_update(Ball_t* ball);

void ball_check(void);

void ball_reset(void);

#endif