/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Function that allow to draw the menu and select option
*/


#include "game.h"

Game* draw_menu(Game* game) {
    TTF_Font* font = NULL;
    SDL_Surface *pong_surf, *host_surf, *connect_surf;
    SDL_Texture *pong_text, *host_text, *connect_text;
    SDL_Rect pong_pos, host_pos, connect_pos, underline_pos;
    int key, select_con;

    SDL_Color white = {255, 255, 255, 255};
    SDL_SetRenderDrawColor( game->pRenderer, 255, 255, 255, 255 );
    key= -2;
    select_con = 1;

    if (TTF_Init() == -1) {
        fprintf(stderr, "[-] An error occured when trying to init ttf : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }


    font = TTF_OpenFont("./res/digital.ttf", 25);
    // Set positions and sizes
    //Logo
    pong_pos.h = 200;
    pong_pos.w = 800;
    pong_pos.x = (game->screenSize.x - pong_pos.w) / 2;
    pong_pos.y = 30;
    // Options
    host_pos.h = 100;
    host_pos.w = 200;
    host_pos.x = (game->screenSize.x) / 2 - (host_pos.w + 30);
    host_pos.y = 0.7 * (game->screenSize.y);
    connect_pos = host_pos;
    host_pos.x  = (game->screenSize.x) / 2 + 30;

    underline_pos = *underline_rect(&connect_pos);

    // Instantiate surfaces
    pong_surf = TTF_RenderText_Solid(font, "PONG", white);
    host_surf = TTF_RenderText_Solid(font, "HOST" , white);
    connect_surf = TTF_RenderText_Solid(font, "CONNECT" , white);

    //Instantiate textures
    pong_text = SDL_CreateTextureFromSurface(game->pRenderer, pong_surf);
    host_text = SDL_CreateTextureFromSurface(game->pRenderer, host_surf);
    connect_text = SDL_CreateTextureFromSurface(game->pRenderer, connect_surf);
    SDL_RenderCopy(game->pRenderer, pong_text, NULL, &pong_pos);
    SDL_RenderCopy(game->pRenderer, host_text, NULL, &host_pos);
    SDL_RenderCopy(game->pRenderer, connect_text, NULL, &connect_pos);
    SDL_RenderPresent(game->pRenderer);

    while(game->game_step == 0) {
        // Handle event

        key = game_event();
        if (key == 3 && select_con == 1) {
            reset_form(game->pRenderer, &underline_pos);
            underline_pos = *underline_rect(&host_pos);
            select_con = 0;
        } else if (key == 4 && select_con == 0) {
            reset_form(game->pRenderer, &underline_pos);
            underline_pos = *underline_rect(&connect_pos);
            select_con = 1;
        } else if (key == 5) {
            game->game_step = 1;
            if (select_con == 1) {
                game->con->is_host = 0;
            } else {
                game->con->is_host = 1;
            }
        } else if (key == -1) {
            game_destroy(game);
            return NULL;
        }
        SDL_RenderFillRect(game->pRenderer, &underline_pos);
        SDL_RenderPresent(game->pRenderer);
    }

    reset_form(game->pRenderer, &underline_pos);
    SDL_DestroyTexture(pong_text);
    SDL_DestroyTexture(host_text);
    SDL_DestroyTexture(connect_text);
    //Clear
    SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0); 
    SDL_RenderFillRect(game->pRenderer, &pong_pos);
    SDL_RenderFillRect(game->pRenderer, &host_pos);
    SDL_RenderFillRect(game->pRenderer, &connect_pos);
    SDL_RenderPresent(game->pRenderer);
    TTF_CloseFont(font);
    TTF_Quit();

    return game;
}




