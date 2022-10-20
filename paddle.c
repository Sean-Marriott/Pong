/**
    @file paddle.c
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Provides the implementation of methods used to interact
           with the game paddle.
*/

#include "paddle.h"
#include "system.h"
#include "navswitch.h"
#include "tinygl.h"

#define START_PADDLE_TOP_X 4
#define START_PADDLE_TOP_Y 4
#define START_PADDLE_BOTTOM_X 4
#define START_PADDLE_BOTTOM_Y 2
#define DISPLAY_TRUE 1
#define DISPLAY_FALSE 0
#define MAX_Y 5
#define MIN_Y 1
#define PADDLE_INCREMENT 1

/** Initializing the paddle for the game */
void paddle_init(void)
{
    paddle.top = tinygl_point(START_PADDLE_TOP_X, START_PADDLE_TOP_Y);
    paddle.bottom = tinygl_point(START_PADDLE_BOTTOM_X,START_PADDLE_BOTTOM_Y);
}

/** Displaying the paddle on the matrix display */
void paddle_display(void) {
    tinygl_draw_line(paddle.top, paddle.bottom, DISPLAY_TRUE);
}

/** Hiding the paddle from the matrix display */
void paddle_hide(void) {
    tinygl_draw_line(paddle.top, paddle.bottom, DISPLAY_FALSE);
}

/** Changing the location of the paddle */
void paddle_move(void) {
    paddle_hide();
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if (paddle.top.y <= MAX_Y) {
            paddle.top.y += PADDLE_INCREMENT;
            paddle.bottom.y += PADDLE_INCREMENT;
        }
    }
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        if (paddle.bottom.y >= MIN_Y) {
            paddle.top.y -= PADDLE_INCREMENT;
            paddle.bottom.y -= PADDLE_INCREMENT;
        }
    }
    paddle_display();
}