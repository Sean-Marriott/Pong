#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "component.h"
#include "vec.h"
#include "navswitch.h"


#define BALL_RATE 5
#define PACER_RATE 100

/** Define PIO pins driving LED matrix rows.  */
static const pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t ledmat_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Resets the matrix display. */
void reset_mat(void)
{
    for (uint8_t row = 0; row < LEDMAT_ROWS_NUM; row++) {
        pio_output_high (ledmat_rows[row]);
    }

    for (uint8_t col = 0; col < LEDMAT_COLS_NUM; col++) {
        pio_output_high (ledmat_cols[col]);
    }
}

/** Returns a new ball */
Ball_t new_ball(void)
{   
   Ball_t ball = {
        .pos = vec(0, 0),
        .force = vec(1, 1)
    };

    return ball;
}



int main (void)
{
    system_init ();
    pacer_init(PACER_RATE);
    ledmat_init();

    Ball_t ball = new_ball();

    Paddle_t paddle = {
        .center = 3,
        .size = 1
    };

    uint8_t cycle = 0;

    uint8_t state = 0;

    while (1)
    {   
        pacer_wait();
        cycle++;

        navswitch_update();
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (paddle.center < LEDMAT_COLS_NUM) {
                paddle.center ++;
            }
        }
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (paddle.center > 1) {
              paddle.center --;
            }
        }

        if (cycle % (PACER_RATE / BALL_RATE) == 0) {
            update(&ball);
        }

        if (state == 0) {
            reset_mat();
            
            pio_output_low(ledmat_cols[4]);
            for (uint8_t row = 0; row < LEDMAT_ROWS_NUM; row++) {
                if (paddle.center+paddle.size == row || paddle.center-paddle.size == row ||paddle.center == row) {
                    pio_output_low (ledmat_rows[row]);
                } else {
                    pio_output_high (ledmat_rows[row]);
                }

            }
            state = 1;
        } else {
            reset_mat();

            for (uint8_t row = 0; row < LEDMAT_ROWS_NUM; row++) {
                if (ball.pos.y == row) {
                    pio_output_low (ledmat_rows[row]);
                } else {
                    pio_output_high (ledmat_rows[row]);
                }

            }

            for (uint8_t col = 0; col < LEDMAT_COLS_NUM; col++){
                if (ball.pos.x == col) {
                    pio_output_low (ledmat_cols[col]);
                } else {
                    pio_output_high (ledmat_cols[col]);
                }
                if (ball.pos.x == LEDMAT_COLS_NUM - 1) {
                    if (ball.pos.y != paddle.center && ball.pos.y != paddle.center+paddle.size && ball.pos.y != paddle.center-paddle.size) {
                        ball = new_ball();
                        // Find a better way to delay here
                        for (int i = 30; i > 0; i--) {
                            pacer_wait();
                        }
                    }  
                } 
            }   
            state = 0;
        }

    }
}
