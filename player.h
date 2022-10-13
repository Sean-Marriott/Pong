#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_SCORE 5

void player_inc_score1(void);

void player_inc_score2(void);

bool player_win_p(void);

bool player_lose_p(void);

uint8_t player_score1(void);

uint8_t player_score2(void);

#endif