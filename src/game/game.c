/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Functions that allow to init the game
*/


#include "game.h"


Game* draw_game(Game* game) {
    SDL_SetRenderDrawColor( game->pRenderer, 255, 255, 255, 255 ); 
    // Draw middle line
    for ( int i = 10; i < game->screenSize.x; i += 60 ) {
        SDL_Rect fillRect = { game->screenSize.x / 2,  i, 7, 40};
        SDL_RenderFillRect( game->pRenderer, &fillRect);
    }
    // Draw rackets
    SDL_RenderFillRect(game->pRenderer, &game->p1Racket);
    SDL_RenderFillRect(game->pRenderer, &game->p2Racket);
    // Draw ball
    SDL_RenderFillRect(game->pRenderer, &game->ball);
    SDL_RenderPresent(game->pRenderer);
    game = draw_score(game);

    return game;
}

Game* draw_score(Game* game) {
    TTF_Font* font = NULL;
    Score* score;
    SDL_Rect pos_score_p1, pos_score_p2; 
    char txt_char1[100] = {0};
    char txt_char2[100] = {0};

     if (TTF_Init() == -1) { 
        fprintf(stderr, "[-] An error occured when trying to init ttf : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    score = malloc(sizeof(*score));

    SDL_Color white = {255, 255, 255, 255};
    font = TTF_OpenFont("./res/digital.ttf", 25);
    if (!font) { 
        printf("Couldn't load font\n");
        exit(EXIT_FAILURE);
    }
    pos_score_p1.x = game->screenSize.x / 2 - 80;
    pos_score_p1.y = 10;
    pos_score_p1.w = 50;
    pos_score_p1.h = 70;

    pos_score_p2 = pos_score_p1;
    pos_score_p2.x = game->screenSize.x / 2 + 40;

    reset_form(game->pRenderer, &pos_score_p1);
    reset_form(game->pRenderer, &pos_score_p2);
   // Cast text to char*
    sprintf(txt_char1, "%d", game->sharedInfo->score[0]);
    sprintf(txt_char2, "%d", game->sharedInfo->score[1]);
    
    // Create surface
    score->surface[0] = TTF_RenderText_Solid(font, txt_char1, white);
    score->surface[1] = TTF_RenderText_Solid(font, txt_char2 , white);
    //Create texture
    score->texture[0] = SDL_CreateTextureFromSurface(game->pRenderer, score->surface[0]);
    score->texture[1] = SDL_CreateTextureFromSurface(game->pRenderer, score->surface[1]);
    
    // Clear  previous
    SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0 ); 
    SDL_RenderFillRect(game->pRenderer, &pos_score_p1);
    SDL_RenderFillRect(game->pRenderer, &pos_score_p2);

    SDL_RenderCopy(game->pRenderer, score->texture[0], NULL, &pos_score_p1);
    SDL_RenderCopy(game->pRenderer, score->texture[1], NULL, &pos_score_p2);
    SDL_RenderPresent(game->pRenderer);

    TTF_CloseFont(font);
    TTF_Quit();

    game->score = score;
    free(score);
    return (game);
}


void game_destroy(Game* game) {
    if (game) {
        if (game->score) {
            if (game->score->surface[0]) {
                SDL_FreeSurface(game->score->surface[0]);
            }
            if (game->score->surface[1]) {
                SDL_FreeSurface(game->score->surface[1]);
            }
            if (game->score->texture[0]) {
                SDL_DestroyTexture(game->score->texture[0]);
            }
            if (game->score->texture[1]) {
                SDL_DestroyTexture(game->score->texture[1]);
            }
        }
        
        if (game->pRenderer) {
            SDL_DestroyRenderer(game->pRenderer);
        }
        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
        }
        SDL_Quit();
        free(game);
    }
}