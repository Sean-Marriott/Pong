#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "vec.h"
#include "navswitch.h"
#include "tinygl.h"
#include "paddle.h"
#include "../fonts/font5x7_1.h"
#include "ball.h"

#define BALL_RATE 5
#define PACER_RATE 500

void game_init(void)
{
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    pacer_init(PACER_RATE);
    ledmat_init();
    paddle_init();
    ball_init();
}

int main (void)
{
    game_init();
    uint8_t cycle = 0;

    while (1)
    {   
        pacer_wait();
        tinygl_update();
        navswitch_update();
        paddle_move();

        cycle++;

        if (cycle % (PACER_RATE / BALL_RATE) == 0) {
            ball_update(&ball);
            ball_check();
        }
    }
}
