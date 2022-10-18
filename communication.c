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
void send_packet(Ball_t ball, uint8_t end)
{   
    ir_uart_putc(end);
    ir_uart_putc(ball.pos.y);
    // Force x-component must be 1
    ir_uart_putc(ball.force.y);
}

/** Recieves packet from the other board */
Packet_t receive_packet(void)
{
    // Initialize empty packet
    Packet_t recieved_packet = {0, 0, 0};
    
    recieved_packet.end = ir_uart_getc();
    recieved_packet.ball_pos_y = ir_uart_getc();
    recieved_packet.ball_force_y = ir_uart_getc();

    return recieved_packet;
}

Packet2_t receive_packet2(void)
{
    // Initialize empty packet
    Packet2_t recieved_packet = {0, 0};
    
    recieved_packet.code = ir_uart_getc();
    recieved_packet.value = ir_uart_getc();

    return recieved_packet;
}

void send_end(void)
{
    ir_uart_putc(END_CODE);
}

void send_level(uint8_t level)
{
    ir_uart_putc(LEVEL_CODE);
    ir_uart_putc(level);
}

