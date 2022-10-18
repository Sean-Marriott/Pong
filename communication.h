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

// Randomly assigned value
#define END_CODE 9
#define LEVEL_CODE 6

/** The packet structure communicated between boards */
typedef struct {

    // Whether or not the game should end
    uint8_t end;
    // The Y-Coordinate of the ball
    uint8_t ball_pos_y;
    // The Y-Component of the ball's force
    uint8_t ball_force_y;
} Packet_t;

typedef struct {
    uint8_t code;
    uint64_t value;
} Packet2_t;

/** Intialising the IR module for the game */
void communication_init(void);

/** Sending the packet to the other board */
void send_packet(Ball_t ball, uint8_t);

/** Recieving packet from the other board */
Packet_t receive_packet(void);

void send_level(uint8_t level);

Packet2_t receive_packet2(void);

#endif