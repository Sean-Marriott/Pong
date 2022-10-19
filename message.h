/**
    @file message.h
    @author Sean Marriott
    @author Claire Kim
    @date 19-10-2022
    @brief Message module header file. Provides methods 
           used to display messages on the LED matrix display.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include "tinygl.h"
#include "../../fonts/font5x5_1.h"

#define MESSAGE_RATE 10

/** Initilizes the message module */
void message_init(uint16_t);

/** Display welcoming message */
void display_welcome(void);

/** Display winner */
void display_winner(void);

/** Display loser */
void display_loser(void);

/** Display difficulty */
void display_difficulty(uint8_t);

#endif