/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Provides a set of utility function
*/


#include "game.h"

void reset_form(SDL_Renderer* renderer, SDL_Rect* form) {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, form);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
}

SDL_Rect* underline_rect(SDL_Rect *rect) {
    SDL_Rect* res;

    res = malloc(sizeof(*res));
    res->y = rect->y + rect->h + 15;
    res->x = rect->x;
    res->w = rect->w;
    res->h = 15;

    return res;
}

int game_event() {
    SDL_Event event;
    int res;

    res = -2;
    //Get back event
    if(SDL_PollEvent(&event)) {
        if(event.type ==  SDL_QUIT) {
            //Leave the game
            res = -1;
        } else if(event.type == SDL_KEYDOWN) {
            //Handle key
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    res = -1;
                    break;
                case SDLK_SPACE:
                    res = 0;
                    break;
                case SDLK_UP:
                    res = 1;
                    break;
                case SDLK_DOWN:
                    res = 2;
                    break;
                case SDLK_RIGHT:
                    res = 3;
                    break;
                case SDLK_LEFT:
                    res = 4;
                    break;
                case SDLK_RETURN:
                    res = 5; 
                    break;
                default:
                    fprintf(stderr, "Unknown key: %d", event.key.keysym.sym);
                    break;
            }
        }
    }
    return res;
}
