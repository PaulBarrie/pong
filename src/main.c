/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		entrypoint of the game
*/

#include "pong.h"

int main() {
    Game* game = game_init();    
    game = draw_menu(game);
    game = draw_connections(game);
    game = play(game); 
    game_destroy(game);
    end_con(game->con); 
    return(EXIT_SUCCESS);
}