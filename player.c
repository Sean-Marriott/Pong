/**
    @file player.c
    @author Sean Marriott
    @author Claire Kim
    @date 18-10-2022
    @brief Module containing the player functionality.
*/

#include "player.h"

/** Initializing players*/
void player_init(uint8_t player_number)
{
    player.number = player_number;
    player.life = MAX_LIVES;
}

void player_lose_life(void)
{
    player.life -= 1;
}

uint8_t player_check_lose(void)
{   
    if (player.life <= 0) {
        return 1;
    } else {
        return 0;
    }
}