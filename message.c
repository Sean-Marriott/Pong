/**
    @file message.c
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Provides the implementation of methods 
           used to display messages on the LED matrix display.
*/

#include "message.h"
#include "tinygl.h"

#define MESSAGE_RATE 10

/** Initilizes the message module 
    @param pacer_rate, the rate of the pacer used */
void message_init(uint16_t pacer_rate)
{
    tinygl_init(pacer_rate);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_font_set(&font5x5_1);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

/** Displays welcoming message */
void display_welcome(void)
{
    tinygl_clear();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("Welcome to Pong!!");
}

/** Displays winner */
void display_winner(void)
{
    tinygl_text("W");
}

/** Displays loser */
void display_loser(void)
{
    tinygl_text("L");
}

/** Displays difficulty 
    @param difficulty_index, the index of the selected difficulty */
void display_difficulty(uint8_t difficulty_index)
{   
    char difficulties[] = {'1', '2', '3'};
    char difficulty_text[] = {difficulties[difficulty_index], '\0'};
    tinygl_clear();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(difficulty_text);
}
