/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Functions providing game updates according to actions and info received
*/

#include "game.h"

Game* play(Game* game) {
    //Handle player's racket move
    // Begin game
    int key;
    SharedInfo* tmp;
    tmp = malloc(sizeof(SharedInfo));
    tmp = sync_data(game->con, game->sharedInfo);
    key = -2;

    while (key!= -1 && game->game_step == 2){
        key = game_event();
        tmp = sync_data(game->con, game->sharedInfo);
        if (game->con->is_host) {
            game = play_host(game, tmp, key);
        } else {
            game = play_cli(game, tmp, key);
        }
        game = sync_textures(game);
        game = draw_game(game);
        SDL_RenderPresent(game->pRenderer);
    }
    
    return game;
}


Game* play_host(Game* game, SharedInfo* tmp, int key) {
    if (game->sharedInfo->playing == 1 && key == 0) {
        SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0); 
        SDL_RenderFillRect(game->pRenderer, &game->ball);
        game = move_ball(game);
        game->sharedInfo->playing = 0;
    } else if(game->sharedInfo->playing == 0) {
        game = handle_player_move(game, key);
        game = handle_ball_move(game);
        game->sharedInfo->p2Pos = tmp->p2Pos;
    } else if (game->sharedInfo->playing == 2 && tmp->playing == 0) {
        game->sharedInfo->playing = 0;
        // Launch ball
        game->sharedInfo->ballPos[0] += game->set.dx;
        game->sharedInfo->ballPos[1] += game->set.dy;
    } 
    tmp = sync_data(game->con, game->sharedInfo);    
    return game;
}

Game* play_cli(Game* game, SharedInfo* tmp, int key) {
    
    memcpy(game->sharedInfo->ballPos, tmp->ballPos, sizeof(tmp->ballPos));
    tmp = sync_data(game->con, game->sharedInfo);
    if (tmp->playing == 2 && key == 0) {
        game->sharedInfo = tmp;
        game->sharedInfo->playing = 0;
    } else if(game->sharedInfo->playing == 0) {
            if(tmp->playing != 2) {
                game = handle_player_move(game, key);
                game->sharedInfo = tmp;
            }
            
    } else if (game->sharedInfo->playing  == 1 || game->sharedInfo->playing == 2) {
        game->sharedInfo->playing = tmp->playing;
        game = init_racket_and_ball(game);
    }
    
    return game;
}



Game* sync_textures(Game* game) {
    SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0 ); 
    SDL_RenderFillRect(game->pRenderer, &game->p1Racket);
    SDL_RenderFillRect(game->pRenderer, &game->p2Racket);
    SDL_RenderFillRect(game->pRenderer, &game->ball);
    SDL_SetRenderDrawColor( game->pRenderer, 255, 255, 255, 255 ); 

    game->p2Racket.y = game->sharedInfo->p2Pos;
    game->p1Racket.y = game->sharedInfo->p1Pos;
    game->ball.x = game->sharedInfo->ballPos[0];
    game->ball.y = game->sharedInfo->ballPos[1];
    return game;
}


