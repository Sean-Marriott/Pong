#include "paddle.h"
#include "system.h"
#include "navswitch.h"
#include "tinygl.h"

void paddle_init(void)
{
    paddle.top = tinygl_point(4, 4);
    paddle.bottom = tinygl_point(4,2);
    paddle_display();
}

void paddle_display(void) {
    tinygl_draw_line(paddle.top, paddle.bottom, 1);
}

void paddle_hide(void) {
    tinygl_draw_line(paddle.top, paddle.bottom, 0);
}

void paddle_move(void) {
    paddle_hide();
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if (paddle.top.y <= LEDMAT_COLS_NUM) {
            paddle.top.y += 1;
            paddle.bottom.y += 1;
        }
    }
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        if (paddle.bottom.y >= 1) {
            paddle.top.y -= 1;
            paddle.bottom.y -= 1;
        }
    }
    paddle_display();
}