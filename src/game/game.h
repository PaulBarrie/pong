/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		game part header file
*/


#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../online/online.h"
#include <string.h>


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define RACKET_SIZE 80
#define RACKET_SPEED 30
#define BALL_SIZE 10 

typedef struct {
    int dx;
    int dy; 
} Set; 


typedef struct {
    SDL_Surface* surface[2];
    SDL_Texture* texture[2];
} Score; 

typedef struct {
    // Screen variables
    SDL_Point screenSize; 
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    SDL_Rect p1Racket;
    SDL_Rect p2Racket;
    SDL_Rect ball;
    Set set;
    Score* score; 
    SharedInfo* sharedInfo;
    ConInfo* con; // 1 if host 0 else
    int game_step; // 0 home; 1: con /wait for con ; 2 play
} Game; 

// init.c
Game* game_init();
Game* init_racket_and_ball(Game*);

// menu.c
Game* draw_menu(Game*);

// connection.c
Game* draw_connections(Game*);
Game* wait_for_connection(Game*);
Game* connect_to_server(Game*);

// game.c
Game* draw_game(Game*);
Game* draw_score(Game*);
void game_destroy(Game*);

// play.c
Game* play(Game*);
Game* play_host(Game*, SharedInfo*, int);
Game* play_cli(Game*, SharedInfo*, int);
Game* sync_textures(Game* game);

// move.c
Game* handle_player_move(Game*, int);
Game* handle_ball_move(Game*);
Game* move_ball(Game*);

// utils.c
void reset_form(SDL_Renderer*, SDL_Rect*);
SDL_Rect* underline_rect(SDL_Rect*);
int game_event();

#endif