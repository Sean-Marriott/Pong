/**
    @file communication.h
    @author Sean Marriott
    @author Claire Kim
    @date 14-10-2022
    @brief Module Containing the ir communction functionality.
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "ir_uart.h"
#include "ball.h"

/** The packet structure communicated between boards */
typedef struct {

    // Can add other things in here like score

    // The Y-Coordinate of the ball
    uint8_t ball_pos_y;
    // The direction the ball is heading in
    uint8_t ball_direction;
} Packet_t;

/** Intialising the IR module for the game */
void communication_init(void);

/** Sending the ball to the other board */
void send_ball(Ball_t ball);

/** Recieving packet from the other board */
Packet_t recieve_packet(void);

#endif