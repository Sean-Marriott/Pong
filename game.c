#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "component.h"
#include "vec.h"

#define BALL_RATE 10
#define PACER_RATE 500

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


int main (void)
{
    system_init ();
    pacer_init(PACER_RATE);
    ledmat_init();

    Ball_t ball = {
        .pos = vec(0, 0),
        .force = vec(1, 1)
    };

    uint8_t cycle = 0;

    while (1)
    {

        pacer_wait();
        cycle++;

        if (cycle % (PACER_RATE / BALL_RATE) == 0) {
            update(&ball);
        }

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
        }

    }
}
