#include "ball.h"
#include "system.h"
#include "tinygl.h"
#include "paddle.h"
#include "player.h"

void ball_init(void)
{   
    ball.pos = vec(0, 0);
    ball.force = vec(1, 1);
    ball.point = tinygl_point(ball.pos.x, ball.pos.y);
    ball_display();
}

void ball_display(void)
{   
    ball.point = tinygl_point(ball.pos.x, ball.pos.y);
    tinygl_draw_point(ball.point, 1);
}

void ball_hide(void)
{
    tinygl_draw_point(ball.point, 0);
}

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

void ball_reset(void)
{
    ball.pos = vec(0, 0);
    ball.force = vec(1, 1);
}


void ball_check(void)
{
    if (ball.pos.x == LEDMAT_COLS_NUM - 1) {
        if (ball.pos.y > paddle.top.y || ball.pos.y < paddle.bottom.y) {
            player_inc_score2();
            ball_reset();
        }
    }
}