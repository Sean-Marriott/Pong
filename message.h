/**
    @file message.h
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Message module header file. Provides methods 
           used to display messages on the LED matrix display.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include "tinygl.h"
#include "../../fonts/font5x5_1.h"

#define MESSAGE_RATE 10

/** Initilizes the message module 
    @param pacer_rate, the rate of the pacer used */
void message_init(uint16_t pacer_rate);

/** Displays welcoming message */
void display_welcome(void);

/** Displays winner */
void display_winner(void);

/** Displays loser */
void display_loser(void);

/** Displays difficulty 
    @param difficulty_index, the index of the selected difficulty */
void display_difficulty(uint8_t difficulty_index);

#endif