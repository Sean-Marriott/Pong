/**
    @file player.h
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Player module header file. Provides the methods
           for the player functionality.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_LIVES 3

/** The definition for player the datatype*/
typedef struct {
    uint8_t number;
    uint8_t life;
} Player_t;

/** Initializing the player */
Player_t player;

/** Initializing the player */
void player_init(uint8_t);

/** Reduces the number of player's life by 1 */
void player_lose_life(void);

/** Checks if the player has lost the game 
    @return 1 if the player has lost, 0 if not
*/
uint8_t player_check_lose(void);

#endif