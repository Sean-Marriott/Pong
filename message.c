#include "message.h"
#include "tinygl.h"

/** Display welcoming message*/
void display_welcome(void)
{
    tinygl_text("Welcome to Pong!!");
}

/** Display winner*/
void display_winner(void)
{
    tinygl_text("Winner :)");
}

/** Display loser*/
void display_loser(void)
{
    tinygl_text("Loser :(");
}

// void display_difficulty(uint8_t difficulty_index)
// {
//     switch (difficulty_index) {
//         case 0 :
//             tinygl_text("EASY");
//             break;
//         case 1 :
//             tinygl_text("MEDIUM");
//             break;
//         case 2 :
//             tinygl_text("HARD");
//             break;
//     }
//}