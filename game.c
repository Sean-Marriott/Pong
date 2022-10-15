#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "vec.h"
#include "navswitch.h"
#include "../../fonts/font5x5_1.h"
#include "tinygl.h"
#include "paddle.h"
#include "ball.h"
#include "communication.h"

#define BALL_RATE_EASY 3
#define BALL_RATE_MEDIUM 5
#define BALL_RATE_HARD 10
#define PACER_RATE 500
#define MESSAGE_RATE 10

typedef enum {
    STARTING_SCREEN,
    LEVEL_SETUP,
    MAIN_SCREEN,
    WAIT
} Screen_t;

char levels[] = {'1', '2', '3'};
uint8_t level_index = 0;
uint8_t game_speed = 0;
bool level_decision = false;

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

void display_level(void)
{
    char level_text[] = {levels[level_index], '\0'};
    show_text(level_text);
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
    tinygl_font_set (&font5x5_1);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

void choose_game_level(uint8_t level_index) {
  if (level_index == 0) {
    game_speed = BALL_RATE_EASY;
  } else if (level_index == 1) {
    game_speed = BALL_RATE_MEDIUM;
  } else if (level_index == 2) { 
    game_speed = BALL_RATE_HARD; 
  } else {
    game_speed = BALL_RATE_MEDIUM;
  }
}


int main(void) {
  game_init();

  Screen_t screen = STARTING_SCREEN;
  uint8_t cycle = 0;

  tinygl_text("Welcome to Pong!!");

  while (1) {
    cycle++;
    pacer_wait();
    tinygl_update();
    navswitch_update();

    switch (screen) {
    case STARTING_SCREEN:
      if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
        tinygl_text("Select the game levels");
        screen = LEVEL_SETUP;
      }
      break;

    case LEVEL_SETUP:
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            if (level_index < 2) {
                level_index++;
            } else {
                level_index = 0;
            }
            display_level();
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            if (level_index > 0) {
                level_index--;
            } else {
                level_index = 2;
            }
            display_level();
        }
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            level_decision = true;
            choose_game_level(level_index);
            tinygl_clear();
            screen = MAIN_SCREEN;
        }
        break;

    case MAIN_SCREEN:
      paddle_move();
      if (cycle % (PACER_RATE / game_speed) == 0) {

        if (check_transfer()) {
          ball_hide();
          // ball_send(ball);
          // screen = WAIT;
        } else {
          ball_update(&ball);
          ball_check();
        }
      }
      break;
    case WAIT:
      paddle_move();
      Packet_t packet = receive_packet();
      receive_ball(packet.ball_pos_y, packet.ball_force_y);
      screen = MAIN_SCREEN;
      break;
    }
  }
}
