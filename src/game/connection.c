#include "game.h"

/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Functions that handle connection steps
*/


Game* draw_connections(Game* game) {
    if(game->con->is_host == 1) {
        game = wait_for_connection(game);
    } else {
        game = connect_to_server(game);
    }
    SDL_RenderPresent(game->pRenderer);
    return game;
}



Game* wait_for_connection(Game* game) {
    TTF_Font* font = NULL;
    SDL_Surface *msg_surf;
    SDL_Texture *msg_text;
    SDL_Rect msg_pos;
    int key;

    SDL_Color white = {255, 255, 255, 255};
    SDL_SetRenderDrawColor( game->pRenderer, 255, 255, 255, 255);

    if (TTF_Init() == -1) {
        fprintf(stderr, "[-] An error occured when trying to init ttf : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    font = TTF_OpenFont("./res/digital.ttf", 10);
    msg_pos.x = 200;
    msg_pos.h = 0.2 * game->screenSize.y;
    msg_pos.w = 0.7 * game->screenSize.x;
    msg_pos.y = (game->screenSize.y - msg_pos.h) /2;
    msg_surf = TTF_RenderText_Solid(font, "WAITING FOR CONNECTION", white);
    msg_text = SDL_CreateTextureFromSurface(game->pRenderer, msg_surf);
    SDL_RenderCopy(game->pRenderer, msg_text, NULL, &msg_pos);
    SDL_RenderPresent(game->pRenderer);
    game->con = init_con(game->con->is_host, "127.0.0.1"); 

    while(game->game_step == 1) {
        key = game_event();
        if (key == -1) {
            game_destroy(game);
            return NULL;
        }
        if (game->con->socket != -1) {
            game->game_step = 2;
        }

    }
    SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0);
    SDL_DestroyTexture(msg_text);
    SDL_RenderFillRect(game->pRenderer, &msg_pos);
    TTF_CloseFont(font);
    TTF_Quit();

    return game;
}

Game* connect_to_server(Game* game) {
    SDL_Event event;
    char text[16]; 
    TTF_Font* font = NULL;
    SDL_Surface *msg_surf, *input_surf;
    SDL_Texture *msg_text, *input_text;
    SDL_Rect msg_pos, input_pos;

    SDL_Color white = {255, 255, 255, 255};
    SDL_SetRenderDrawColor( game->pRenderer, 0, 0, 0, 0);


    if (TTF_Init() == -1) {
        fprintf(stderr, "[-] An error occured when trying to init ttf : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    font = TTF_OpenFont("./res/digital.ttf", 10);

    //Text
    msg_pos.h = 150;
    msg_pos.w = 800;
    msg_pos.x = 100;
    msg_pos.y = 30;
    // Input
    input_pos.y = msg_pos.y + msg_pos.h + 100;
    input_pos.w = 400;
    input_pos.h = 100;
    input_pos.x = (game->screenSize.x - input_pos.w) / 2;

    msg_surf = TTF_RenderText_Solid(font, "ENTER IP SERVER:" , white);
    msg_text = SDL_CreateTextureFromSurface(game->pRenderer, msg_surf);
    SDL_RenderCopy(game->pRenderer, msg_text, NULL, &msg_pos);
    SDL_RenderPresent(game->pRenderer);

    SDL_StartTextInput();
    while (game->game_step == 1) {
        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_StopTextInput();
                game_destroy(game);
                return NULL;
            } else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
                system("clear"); 
                if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0) {
                    text[strlen(text) - 1] = 0;
                } else if (event.type == SDL_TEXTINPUT) {
                    strcat(text, (char*) event.text.text);
                } else if ( event.key.keysym.sym == SDLK_RETURN && strlen(text) > 7) {
                    game->con = init_con(0, text); 
                    game->game_step = 2;
                }
                SDL_DestroyTexture(input_text);
                SDL_RenderFillRect(game->pRenderer, &input_pos);
                SDL_RenderPresent(game->pRenderer);
                input_surf = TTF_RenderText_Solid(font, text + 2, white);
                input_text = SDL_CreateTextureFromSurface(game->pRenderer, input_surf);
                SDL_RenderCopy(game->pRenderer, input_text, NULL, &input_pos);
                SDL_RenderPresent(game->pRenderer);
            } 
            
        }
    }
    SDL_DestroyTexture(input_text);
    SDL_DestroyTexture(msg_text);
    SDL_RenderFillRect(game->pRenderer, &input_pos);
    SDL_RenderFillRect(game->pRenderer, &msg_pos);
    
    SDL_StopTextInput();
    return game;
}
