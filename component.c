#include "component.h"

void setPosition(Ball_t* ball, Vec_t pos) {
    ball->pos = pos;
}

void update(Ball_t* ball) {
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
}