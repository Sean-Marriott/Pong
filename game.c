#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "vec.h"
#include "navswitch.h"
#include "tinygl.h"
#include "paddle.h"
#include "player.h"
#include "../../fonts/font5x5_1.h"
#include "ball.h"
#include "communication.h"
#include "message.h"

#define BALL_RATE_EASY 3
#define BALL_RATE_MEDIUM 5
#define BALL_RATE_HARD 10
#define PACER_RATE 500
#define MESSAGE_RATE 10
#define LED_PIO PIO_DEFINE(PORT_C, 2)

typedef enum {
  SETUP,
  LEVEL_SELECT,
  PLAYING,
  WAITING,
  END
} State_t;

char levels[] = {'1', '2', '3'};
uint8_t level_index = 0;
uint8_t game_speed = 0;
bool level_decision = false;
State_t state = SETUP;

void game_init(void)
{
    system_init ();
    tinygl_init (PACER_RATE);
    pacer_init(PACER_RATE);
    ledmat_init();
    paddle_init();
    ball_init();
    communication_init();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

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
  ir_uart_putc(game_speed);
}

int main (void)
{
    game_init();
    uint8_t cycle = 0;
    game_speed = 3;
    display_welcome();

    while (1)
    {   
        cycle++;
        pacer_wait();
        tinygl_update();
        navswitch_update();
        switch (state)
        {
          case SETUP:
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
              tinygl_clear();
              tinygl_text("Select difficulty");
              player_init(1);
              state = LEVEL_SELECT;
              break;
            } 
            if (ir_uart_read_ready_p()) {
              tinygl_clear();
              player_init(2);
              game_speed = ir_uart_getc();
              state = WAITING;
            }
            break;
          case LEVEL_SELECT:
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
              state = PLAYING;
          }
          break;

        case PLAYING:
          paddle_move();
          pio_output_low(LED_PIO);
          if (cycle % (PACER_RATE / game_speed) == 0) {
            if (player_check_lose()) {
              tinygl_clear();
              state = END;
              send_packet(ball, player_check_lose());
            } else if (check_transfer()) {
              ball_hide();
              send_packet(ball, player_check_lose());
              state = WAITING;
            } else {
              ball_update(&ball);
              ball_check();
            }
          }
          break;
        
        case WAITING:
          paddle_move();
          pio_output_high(LED_PIO);
          if (ir_uart_read_ready_p()) {
            Packet_t packet = receive_packet();
            receive_ball(packet.ball_pos_y, packet.ball_force_y);
            if (packet.end) {
              tinygl_clear();
              state = END;
            } else {
              state = PLAYING;
            }
          }
          break; 
        case END:
          if (player_check_lose()) {
            display_loser();
          } else {
            display_winner();
          }
          break;
        }
    }
}
