/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Functions that allow to init the game
*/



#include "game.h"



Game* game_init() {
    Game* game = NULL;
    game = malloc(sizeof(*game));
    game->screenSize.x = SCREEN_WIDTH;
    game->screenSize.y = SCREEN_HEIGHT;
    game->game_step = 0;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->sharedInfo = malloc(sizeof(*game->sharedInfo));
    game->sharedInfo->score[0] = 0;
    game->sharedInfo->score[1] = 0;
    game->sharedInfo->playing = 2;
    game->con = malloc(sizeof(*game->con));
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Can't init SDL: %s \n", SDL_GetError());
        game_destroy(game);
    }
    // Create window
    game->pWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, 
                    SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);
    // Init background
    SDL_SetRenderDrawColor( game->pRenderer, 255, 0, 0, 255 );
    // Clear window
    SDL_RenderClear(game->pRenderer);

    if (game->pWindow) {
        //Create renderer
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
        if(!game->pRenderer) {
            fprintf(stderr, "Can't create SDL's renderer: \%s \n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        game = init_racket_and_ball(game);

    }
    return game;
}

Game* init_racket_and_ball(Game* game) {
    // Remove former rackets and balls
    SDL_Rect initRacketP1 = { 5, (game->screenSize.y - RACKET_SIZE) / 2, 10, RACKET_SIZE};
    SDL_Rect initRacketP2 = { game->screenSize.x - 15, (game->screenSize.y - RACKET_SIZE) / 2, 10, RACKET_SIZE};

    SDL_Rect initBallValue = { game->screenSize.x - 25, game->screenSize.y / 2 - BALL_SIZE, BALL_SIZE, BALL_SIZE};
    SDL_SetRenderDrawColor(game->pRenderer, 0, 0, 0, 0);
    SDL_RenderFillRect(game->pRenderer, &game->p1Racket);
    SDL_RenderFillRect(game->pRenderer, &game->p2Racket);
    SDL_RenderFillRect(game->pRenderer, &game->ball);
    SDL_SetRenderDrawColor( game->pRenderer, 255, 255, 255, 255);

    // Init rackets

    game->p1Racket = initRacketP1;
    game->p2Racket = initRacketP2;
    game->sharedInfo->p1Pos = game->p1Racket.y;
    game->sharedInfo->p2Pos = game->p2Racket.y;
    // Init ball

    if (game->sharedInfo->playing == 2) {
        // Give the ball to player
        game->ball = initBallValue;
        // Init direction
        game->set.dx = -3;
        game->set.dy = 1;
    } else if (game->sharedInfo->playing == 1){
        SDL_Rect initBallValue = { 15, game->screenSize.y / 2 - BALL_SIZE, BALL_SIZE, BALL_SIZE};
        game->ball = initBallValue;
        game->set.dx = 3;
        game->set.dy = 1;
    }
    game->sharedInfo->ballPos[0] = game->ball.x;
    game->sharedInfo->ballPos[1] = game->ball.y;
    return game;
}
