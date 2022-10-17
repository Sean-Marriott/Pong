/**
    @file ball.c
    @author Sean Marriott
    @author Claire Kim
    @date 18-10-2022
    @brief Module containing the ball functionality.
*/

#include "ball.h"
#include "system.h"
#include "tinygl.h"
#include "paddle.h"
#include "player.h"

/** Initializes a ball and displays it */
void ball_init(void)
{   
    ball.pos = vec(0, 0);
    ball.force = vec(1, 1);
    ball_display();
}

/** Displays the ball on the matrix */
void ball_display(void)
{   
    ball.point = tinygl_point(ball.pos.x, ball.pos.y);
    tinygl_draw_point(ball.point, 1);
}

/** Removes the ball from the matrix */
void ball_hide(void)
{
    tinygl_draw_point(ball.point, 0);
}

/** Updates the ball's location */
void ball_update(Ball_t* ball) 
{   
    ball_hide();
    ball->pos = vec_add(ball->pos, ball->force);
    if (ball->pos.x < 0) {
        ball->pos = vec(0, ball->pos.y);
        ball->force = vec(-ball->force.x, ball->force.y);
        ball->pos = vec_add_x(ball->pos, ball->force);
    }
    if (ball->pos.y < 0){
        ball->pos = vec(ball->pos.x, 0);
        ball->force = vec(ball->force.x, -ball->force.y);
        ball->pos = vec_add_y(ball->pos, ball->force);
    }
    if (ball->pos.x >= 5){
        ball->pos = vec(4, ball->pos.y);
        ball->force = vec(-ball->force.x, ball->force.y);
        ball->pos = vec_add_x(ball->pos, ball->force);
    }
    if (ball->pos.y >= 7){
        ball->pos = vec(ball->pos.x, 6);
        ball->force = vec(ball->force.x, -ball->force.y);
        ball->pos = vec_add_y(ball->pos, ball->force);
    }
    ball_display();
}

/** Resets the ball's attributes */
void ball_reset(void)
{
    ball.pos = vec(0, 0);
    ball.force = vec(1, 1);
}

/** Checks if the ball has hit the paddle or not */
void ball_check(void)
{
    if (ball.pos.x == LEDMAT_COLS_NUM - 1) {
        if (ball.pos.y > paddle.top.y || ball.pos.y < paddle.bottom.y) {
            player_inc_score2();
            ball_reset();
        }
    }
}

/** Checks if the ball is ready to be sent to the other board */
int check_transfer(void)
{
    // Heading towards the other board
    if (ball.pos.x == 0 && ball.force.x == -1) {
        return 1;
    }
    return 0;
}

/** Sets the ball's attributes based on the parameters received from the other board */
void receive_ball(uint8_t pos_y, uint8_t force_y) {
    ball.pos.x = 0;
    ball.pos.y = pos_y;
    ball.force.x = 1;
    ball.force.y = force_y;  
    ball_display();
}

