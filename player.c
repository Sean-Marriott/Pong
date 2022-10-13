#include "player.h"

static uint8_t score1 = 0;
static uint8_t score2 = 0;

void player_inc_score1(void)
{
    score1 += 1;
}

void player_inc_score2(void)
{
    score2 += 1;
}

bool player_win_p(void)
{
    return score1 >= MAX_SCORE;
}

bool player_lose_p(void)
{
    return score2 >= MAX_SCORE;
}

uint8_t player_score1(void)
{
    return score1;
}

uint8_t player_score2(void)
{
    return score2;
}