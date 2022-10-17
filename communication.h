/**
    @file communication.h
    @author Sean Marriott
    @author Claire Kim
    @date 14-10-2022
    @brief Communication module header file.
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
    // The Y-Component of the ball's force
    uint8_t ball_force_y;
} Packet_t;

/** Intialising the IR module for the game */
void communication_init(void);

/** Sending the packet to the other board */
void send_packet(Ball_t ball);

/** Recieving packet from the other board */
Packet_t receive_packet(void);

#endif