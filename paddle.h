#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"

typedef struct {
    tinygl_point_t bottom;
    tinygl_point_t top;
    
} Paddle_t;

Paddle_t paddle;

void paddle_init(void);

void paddle_display(void);

void paddle_hide(void);

void paddle_move(void);
#endif