/**
    @file paddle.h
    @author Sean Marriott
    @author Claire Kim
    @date 18-10-2022
    @brief Paddle module header file
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"

/** The structure for a paddle */
typedef struct {
    tinygl_point_t bottom;
    tinygl_point_t top;
    
} Paddle_t;

/** The instance of the paddle used */
Paddle_t paddle;

/** Initilizes the paddle */
void paddle_init(void);

/** Display the paddle on the board */
void paddle_display(void);

/** Hide the paddle on the board */
void paddle_hide(void);

/** Change the location of the paddle */
void paddle_move(void);
#endif