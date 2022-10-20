/**
    @file ball.h
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Ball module header file. Provides the methods
           for the ball functionality.
*/

#ifndef BALL_H
#define BALL_H

#include "system.h"
#include "tinygl.h"
#include "vec.h"

/** Definition of the Ball_t datatype */
typedef struct {
    tinygl_point_t point;
    Vec_t pos;
    Vec_t force;
} Ball_t;

/** Instance of the ball used */
Ball_t ball;

/** Initializes the ball */
void ball_init(void);

/** Displays the ball on the matrix display */
void ball_display(void);

/** Updates the ball's attributes 
    @param ball, pointer to the ball data */
void ball_update(Ball_t* ball);

/** Checks if the ball has collided with the paddle */
void ball_check_paddle(void);

/** Resets the attributes of the ball */
void ball_reset(void);

/** Removes the ball from the matrix display */
void ball_hide(void);

/** Checks if the ball is ready to be transfered to the other board 
    @return 1 if the ball is ready to be transfered, 0 if not */
uint8_t check_transfer(void);

/** Sets the ball's attributes based on the parameters received from the other board 
    @param pos_y, the y-position of the ball
    @param force_y, the y component of the ball's force */
void receive_ball(uint8_t pos_y, uint8_t force_y);

#endif