/**
    @file ball.c
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Provides the implementation of methods 
           used to create ball functionality.
*/

#include "system.h"
#include "ball.h"
#include "tinygl.h"
#include "paddle.h"
#include "player.h"

#define STARTING_POSITION_X 0
#define STARTING_POSITION_Y 0
#define STARTING_FORCE_X 1
#define STARTING_FORCE_Y 1
#define TOWARDS_FORCE_X 1
#define AWAY_FORCE_X -1
#define TOWARDS_FORCE_X 1
#define DISPLAY_TRUE 1
#define DISPLAY_FALSE 0
#define MIN_ROW 0
#define MAX_ROW 6
#define NUM_ROWS 7
#define MIN_COLUMN 0
#define MAX_COLUMN 4
#define NUM_COLUMNS 5
#define TRUE 1
#define FALSE 0

/** Initializes a ball and displays it */
void ball_init(void)
{   
    ball.pos = vec(STARTING_POSITION_X, STARTING_POSITION_Y);
    ball.force = vec(STARTING_FORCE_X, STARTING_FORCE_Y);
}

/** Displays the ball on the matrix */
void ball_display(void)
{   
    ball.point = tinygl_point(ball.pos.x, ball.pos.y);
    tinygl_draw_point(ball.point, DISPLAY_TRUE);
}

/** Removes the ball from the matrix */
void ball_hide(void)
{
    tinygl_draw_point(ball.point, DISPLAY_FALSE);
}

/** Updates the ball's location 
    @param ball, pointer to the ball data */
void ball_update(Ball_t* ball) 
{   
    ball_hide();
    ball->pos = vec_add(ball->pos, ball->force);
    if (ball->pos.x < MIN_COLUMN) {
        ball->pos = vec(0, ball->pos.y);
        ball->force = vec(-ball->force.x, ball->force.y);
        ball->pos = vec_add_x(ball->pos, ball->force);
    }
    if (ball->pos.y < MIN_ROW){
        ball->pos = vec(ball->pos.x, MIN_ROW);
        ball->force = vec(ball->force.x, -ball->force.y);
        ball->pos = vec_add_y(ball->pos, ball->force);
    }
    if (ball->pos.x >= NUM_COLUMNS){
        ball->pos = vec(MAX_COLUMN, ball->pos.y);
        ball->force = vec(-ball->force.x, ball->force.y);
        ball->pos = vec_add_x(ball->pos, ball->force);
    }
    if (ball->pos.y >= NUM_ROWS){
        ball->pos = vec(ball->pos.x, MAX_ROW);
        ball->force = vec(ball->force.x, -ball->force.y);
        ball->pos = vec_add_y(ball->pos, ball->force);
    }
    ball_display();
}

/** Checks if the ball has hit the paddle or not */
void ball_check_paddle(void)
{
    if (ball.pos.x == MAX_COLUMN) {
        if (ball.pos.y > paddle.top.y || ball.pos.y < paddle.bottom.y) {
            player_lose_life();
            ball_init();
        }
    }
}

/** Checks if the ball is ready to be sent to the other board 
    @return 1 if the ball is ready to be transfered, 0 if not */
uint8_t check_transfer(void)
{
    // Heading towards the other board
    if (ball.pos.x == MIN_COLUMN && ball.force.x == AWAY_FORCE_X) {
        return TRUE;
    }
    return FALSE;
}

/** Sets the ball's attributes based on the parameters received from the other board
    @param pos_y, the y-position of the ball
    @param force_y, the y component of the ball's force */
void receive_ball(uint8_t pos_y, uint8_t force_y) {
    ball.pos.x = STARTING_POSITION_X;
    ball.pos.y= MAX_ROW - pos_y;
    ball.force.x = TOWARDS_FORCE_X;
    ball.force.y = -force_y;  
    ball_display();
}

