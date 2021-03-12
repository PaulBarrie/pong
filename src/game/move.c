/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Functions that allow to handle ball and player move
*/


#include "game.h"

Game* handle_player_move(Game* game, int key) {
    SDL_Rect pRacket;
    int pPos;
    if (game->con->is_host) {
        pRacket = game->p1Racket;
        pPos = game->sharedInfo->p1Pos;
    } else {
        pRacket = game->p2Racket;
        pPos = game->sharedInfo->p2Pos;
    }
    if (key > 0 && game->sharedInfo->playing == 0) {
        SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0); 
        if (key == 1) {
            if(pPos  > 10) {
                SDL_RenderFillRect(game->pRenderer, &pRacket);
                pRacket.y -= RACKET_SPEED;
                pPos -= RACKET_SPEED;
            }
        } else if(key == 2) {
            if (pPos + 80 <= game->screenSize.y) {
                SDL_RenderFillRect(game->pRenderer, &pRacket);
                pRacket.y += RACKET_SPEED;
                pPos += RACKET_SPEED;
            }
        }
        if (game->con->is_host) {
            game->p1Racket = pRacket;
            game->sharedInfo->p1Pos = pPos;
        } else {
            game->p2Racket = pRacket;
            game->sharedInfo->p2Pos = pPos;
        }
    }
    
    return game;
}

Game* handle_ball_move(Game* game) {
    //Up down limit
    if(game->sharedInfo->ballPos[1] <= 0 || game->sharedInfo->ballPos[1] >= game->screenSize.y) {
        game->set.dy *= -1;
        game = move_ball(game);
    } else if (game->sharedInfo->ballPos[0] + 10 >= game->screenSize.x) {
        // Player 1 wins
        game->sharedInfo->score[0]++;
        game->sharedInfo->playing = 2;
        game = init_racket_and_ball(game);
    } else if (game->sharedInfo->ballPos[0] <= 0 && game->sharedInfo->playing == 0) {
        // Player 2 wins
        game->sharedInfo->score[1]++;
        game->sharedInfo->playing = 1;
        game = init_racket_and_ball(game);
    } else if (game->sharedInfo->ballPos[0] <= 15 && 
        (game->sharedInfo->ballPos[1] + 10 >= game->sharedInfo->p1Pos &&  
        game->sharedInfo->ballPos[1] <= game->sharedInfo->p1Pos+ 80) ) {
        // Touch player 1 racket
        game->set.dx *= -1.05;
        game->set.dy =  (game->sharedInfo->ballPos[1] + 5 - game->sharedInfo->p2Pos + 40) * 0.02;
        game = move_ball(game);
    } else if(game->sharedInfo->ballPos[0] + 10 >= game->screenSize.x - 15 && 
        (game->sharedInfo->ballPos[1] + 10 >= game->sharedInfo->p2Pos &&  
        game->sharedInfo->ballPos[1] <= game->sharedInfo->p2Pos + 80)) {
        // Touch player 2 racket
        game->set.dx *= -1.05;
        game->set.dy =  (game->sharedInfo->ballPos[1] + 5 - game->sharedInfo->p2Pos + 40) * 0.02;
        game = move_ball(game);
    } 
    // Move ball
    else {
        game = move_ball(game);
    }
    return game;
}

Game* move_ball(Game* game) {
    game->sharedInfo->ballPos[0] += game->set.dx;
    game->sharedInfo->ballPos[1] += game->set.dy;
    return game;
}

