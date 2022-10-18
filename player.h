/**
    @file player.h
    @author Sean Marriott
    @author Claire Kim
    @date 18-10-2022
    @brief Player module header file
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_LIVES 2

/** The definition for player the datatype*/
typedef struct {
    uint8_t number;
    uint8_t life;
} Player_t;

Player_t player;

void player_init(uint8_t);

void player_lose_life(void);

uint8_t player_check_lose(void);

#endif