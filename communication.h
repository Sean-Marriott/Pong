/**
    @file communication.h
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Communication module header file.
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "ir_uart.h"
#include "ball.h"

// Randomly assigned values
#define END_CODE 9
#define DIFFICULTY_CODE 6
#define BALL_CODE 4

/** The packet structure communicated between boards */
typedef struct {
    // The code describing what the packet entails
    uint8_t code;
    // The first parameter in the packet
    uint8_t param_1;
    // The second parameter in the packet
    uint8_t param_2;
} Packet_t;

/** Intialising the IR module for the game */
void communication_init(void);

/** Sending the ball information to the other board 
    @param ball, the ball to be sent */
void send_ball(Ball_t ball);

/** Sending the level information to the other board
    @param difficulty, the integer representation of the difficulty to be sent */
void send_difficulty(uint8_t difficulty);

/** Sending the end information to the other board */
void send_end(void);

/** Recieving packet from the other board 
    @return the packet of data recieved */
Packet_t receive_packet(void);

#endif