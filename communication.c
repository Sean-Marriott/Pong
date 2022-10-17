/**
    @file communication.c
    @author Sean Marriott
    @author Claire Kim
    @date 14-10-2022
    @brief Module containing the ir communication functionality.
*/

#include "communication.h"
#include "ir_uart.h"
#include "ball.h"

/** Intialising the IR module for the game */
void communication_init(void)
{
    ir_uart_init();
}

/** Sends the ball to the other board */
void send_packet(Ball_t ball)
{
    ir_uart_putc(ball.pos.y);
    // Force x-component must be 1
    ir_uart_putc(ball.force.y);
}

/** Recieves packet from the other board */
Packet_t receive_packet(void)
{
    // Initialize empty packet
    Packet_t recieved_packet = {0, 0};
    
    recieved_packet.ball_pos_y = ir_uart_getc();
    recieved_packet.ball_force_y = ir_uart_getc();

    return recieved_packet;
}
