#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "vec.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "paddle.h"
#include "../fonts/font5x7_1.h"
#include "ball.h"

#define BALL_RATE 10
#define PACER_RATE 500
#define MESSAGE_RATE 10

typedef enum {
    STARTING_SCREEN,
    MAIN_SCREEN
} Screen_t;

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

static uint8_t score = 0;

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

void check_winner(uint8_t player1, uint8_t player2)
{
    if (player1 > player2) {
        tinygl_text("WIN P1");
    } else {
        tinygl_text("WIN P2");
    }

    //Reinitialise game
    reset_mat();
    tinygl_clear();
}

void show_text(char *text)
{
    tinygl_clear();
    tinygl_text(text);
}

void display_scores(void)
{
    char message[] = {'0' + score, '\0'};
    show_text(message);
}

void game_init (void)
{
    system_init ();
    pacer_init(PACER_RATE);
    ledmat_init();
    paddle_init();
    ball_init();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

int main (void)
{
    game_init();

    Screen_t screen = STARTING_SCREEN;
    uint8_t cycle = 0;

    tinygl_text("Welcome to Pong!!");

    while (1)
    {   
        cycle++;
        pacer_wait();
        tinygl_update();
        navswitch_update();

        switch (screen) {
            case STARTING_SCREEN:
                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    tinygl_clear();
                    screen = MAIN_SCREEN;
                }
                break;
            case MAIN_SCREEN:
                paddle_move();

                if (cycle % (PACER_RATE / BALL_RATE) == 0) {
                    ball_update(&ball);
                    ball_check();
                }
                break;
        }
    }
}
