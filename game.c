#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "vec.h"
#include "navswitch.h"
#include "tinygl.h"
#include "paddle.h"
#include "player.h"
#include "ball.h"
#include "communication.h"
#include "message.h"

#define START_CYCLE 0
#define START_SPEED 0
#define START_INDEX 0
#define BALL_RATE_EASY 3
#define BALL_RATE_MEDIUM 5
#define BALL_RATE_HARD 7
#define PACER_RATE 500
#define PLAYER_1 1
#define PLAYER_2 2
#define MAX_DIFFICULTY_INDEX 2
#define MIN_DIFFICULTY_INDEX 0
#define LED_PIO PIO_DEFINE(PORT_C, 2)

typedef enum {
  SETUP,
  DIFFICULTY_SELECT,
  PLAYING,
  WAITING,
  END
} State_t;

uint8_t cycle = START_CYCLE;
uint8_t game_speed = START_SPEED;
uint8_t level_index = START_INDEX;
State_t state = SETUP;

/** Initilizes the various modules used in the game */
void game_init(void)
{
    system_init();
    ledmat_init();
    paddle_init();
    ball_init();
    communication_init();
    message_init(PACER_RATE);
    pacer_init(PACER_RATE);
}

/** Sets the game difficulty
    @param difficulty_index, the index of the select difficulty
 */
void set_difficulty(uint8_t difficulty_index) {
  switch (difficulty_index) {
    case 0: 
      game_speed = BALL_RATE_EASY;
      break;
    case 1:
      game_speed = BALL_RATE_MEDIUM;
      break;
    case 2:
      game_speed = BALL_RATE_HARD; 
      break;
  }
  // Sends the chosen game difficulty to the other board
  send_difficulty(game_speed);
}

/** Tasks for the board in the playing state */
void playing_tasks(void) 
{
  // Turns off the blue led, signifies the board is not waiting for a signal
  pio_output_low(LED_PIO);
  paddle_move();
  if (cycle % (PACER_RATE / game_speed) == 0) {
    // If the player has lost all their lives, end the game and send an end signal to the other board
    if (player_check_lose()) {
      tinygl_clear();
      state = END;
      send_end();
    // If ready, send the ball to the other board and change the state to WAITING
    } else if (check_transfer()) {
      ball_hide();
      send_ball(ball);
      state = WAITING;
    // Else, update the position of the ball on the board and check if it has collided with the paddle
    } else {
      ball_update(&ball);
      ball_check_paddle();
    }
  }
}

/** Tasks for the board in the setup state */
void setup_tasks(void)
{
  // If the player presses down the navswitch they are player 1 so send them to the difficulty select state
  if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    tinygl_clear();
    display_difficulty(level_index);
    player_init(PLAYER_1);
    state = DIFFICULTY_SELECT;
  // Else, if they recieve a difficulty code they are player 2 so send them to the waiting state
  } else if (ir_uart_read_ready_p()) {
    Packet_t packet = receive_packet();
    if (packet.code == DIFFICULTY_CODE) {
      tinygl_clear();
      player_init(PLAYER_2);
      game_speed = packet.param_1;
      state = WAITING; 
    }
  }
}

/** Tasks for the board in the difficulty select state */
void difficulty_select_tasks(void)
{
  // Increasing the difficulty on pushing the navswitch north
  if (navswitch_push_event_p(NAVSWITCH_NORTH) && level_index < MAX_DIFFICULTY_INDEX) {
    level_index++; 
    display_difficulty(level_index);
  // Decreasing the difficulty on pushing the navswitch south
  }else if (navswitch_push_event_p(NAVSWITCH_SOUTH) && level_index > MIN_DIFFICULTY_INDEX) {
    level_index--;
    display_difficulty(level_index);
  // Chosing the difficulty on pressing the navswitch in and sending them to the playing state
  }else if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    set_difficulty(level_index);
    tinygl_clear();
    state = PLAYING;
  }
}

/** Tasks for the board in the waiting state */
void waiting_tasks(void)
{
  // Activating the blue led indicating that it is waiting for a signal from the other board
  pio_output_high(LED_PIO);
  paddle_move();
  if (ir_uart_read_ready_p()) {
    Packet_t packet = receive_packet();
    receive_ball(packet.param_1, packet.param_2);
    if (packet.code == END_CODE) {
      tinygl_clear();
      state = END;
    } else {
      state = PLAYING;
    }
  }
}

/** Tasks for the board in the end state */
void end_tasks(void)
{
  // Turns off the blue led, signifies the board is not waiting for a signal
  pio_output_low(LED_PIO);
  // If the player has lost display the loser message
  if (player_check_lose()) {
    display_loser();
  // Else the player has won, display the winner message
  } else {
    display_winner();
  }
  // If the player pressing the navswitch down, restart the game by sending them back to the setup state
  if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    tinygl_clear();
    display_welcome();
    paddle_init();
    ball_init();
    state = SETUP;
  }
}

/** Runs the game 
    @return indicates how the program exited, 0 for normal
*/
int main (void)
{
    // Initilize the modules used in the game
    game_init();
    // Display the welcome text
    display_welcome();
    // Game loop
    while (1)
    {   
      cycle++;
      pacer_wait();
      tinygl_update();
      navswitch_update();
      // Running the appropriate tasks based on the game state
      switch (state)
      {
      case SETUP:
        setup_tasks();
        break;
      case DIFFICULTY_SELECT:
        difficulty_select_tasks();
        break;
      case PLAYING:
        playing_tasks();
        break;
      case WAITING:
        waiting_tasks();
        break; 
      case END:
        end_tasks();
        break;
      }
    }
}
