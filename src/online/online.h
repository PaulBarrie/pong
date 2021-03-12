/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		online part header file
*/


#ifndef ONLINE_H
#define ONLINE_H

#define PORT 8000
#define ADDRESS "127.0.0.1" 

#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 
#include<cjson/cJSON.h>

typedef struct {
    int ballPos[2];
    int p1Pos;
    int p2Pos;
    int score[2];
    int playing; // 1 if ball to P1, 2 if ball to P2; 0 else
} SharedInfo;


typedef struct {
    int socket;
    int is_host; //1 if host else 0
    char* addr;
} ConInfo; 

// server.c
int run_server();
char* serve(ConInfo*, char*);

// client.c
int connect_server(const char*);
char* send_to_server(ConInfo*, char*);

// online.c
ConInfo* init_con(int, char*);
void end_con(ConInfo*);
SharedInfo* sync_data(ConInfo*, SharedInfo*);

// encode_decode.c
char* encode_data(SharedInfo*, int);
SharedInfo* decode_data(const char*, int);
#endif