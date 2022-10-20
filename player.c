/**
    @file player.c
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Provides the implementation of methods 
           used to create player functionality.
*/

#include "player.h"

#define MAX_LIVES 3

/** Initializing the player */
void player_init(uint8_t player_number)
{
    player.number = player_number;
    player.life = MAX_LIVES;
}

/** Reduces the number of player's life by 1 */
void player_lose_life(void)
{
    player.life -= 1;
}

/** Checks if the player has lost the game 
    @return 1 if the player has lost, 0 if not
*/
uint8_t player_check_lose(void)
{   
    if (player.life <= 0) {
        return 1;
    } else {
        return 0;
    }
}