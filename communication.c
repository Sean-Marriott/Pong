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

/** Sending the ball information to the other board */
void send_ball(Ball_t ball)
{   
    // Tell the other board it is receiving a ball
    ir_uart_putc(BALL_CODE);
    // Send the ball's y position
    ir_uart_putc(ball.pos.y);
    // Don't need to send the ball's x position, as it must be 1
    // Send the ball's force component
    ir_uart_putc(ball.force.y);
}

/** Send an end code to the other board */
void send_end(void)
{   
    // Send the end code to the other board
    ir_uart_putc(END_CODE);
}

/** Send the level information to the other board*/
void send_level(uint8_t level)
{
    // Send the level code to the other board
    ir_uart_putc(DIFFICULTY_CODE);
    // Send the level information to the other board
    ir_uart_putc(level);
}

/** Recieves packet of information from the other board */
Packet_t receive_packet(void)
{
    // Initialize an empty packet
    Packet_t recieved_packet = {0, 0, 0};
    if (ir_uart_read_ready_p()) {
        recieved_packet.code = ir_uart_getc();
        if (recieved_packet.code == BALL_CODE) {
            recieved_packet.param_1 = ir_uart_getc();
            recieved_packet.param_2 = ir_uart_getc();
        } else if (recieved_packet.code == DIFFICULTY_CODE) {
            recieved_packet.param_1 = ir_uart_getc();
        }
    }
    return recieved_packet;
}



