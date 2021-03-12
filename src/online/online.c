/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Provides main functions to ensure cli/host connection
*/


#include "online.h"

ConInfo* init_con(int is_host, char* addr) {
    ConInfo* con = NULL;
    con = malloc(sizeof(ConInfo));
    if (is_host == 1) {
        con->socket = run_server();
        con->is_host = 1;
    } else {
        con->socket = connect_server(addr);
        con->is_host = 0;
        con->addr = addr;
    }
    // Check if everything was ok
    if (con->socket == -1) {
            exit(EXIT_FAILURE);
            end_con(con);
            return NULL;
    }
    return con;
}

SharedInfo* sync_data(ConInfo* con, SharedInfo* info) {
    char* to_send;
    char* rec;
    SharedInfo* parsed_info;
    
    rec = malloc(sizeof(char) * 1024);
    parsed_info = malloc(sizeof(*parsed_info));
    
    to_send = encode_data(info, con->is_host); 
    if (con->is_host == 1) {
        rec = serve(con, to_send);
        parsed_info = decode_data(rec, con->is_host);
        info->p2Pos = parsed_info->p2Pos;
        if (parsed_info->playing >= 0 && parsed_info->playing <= 2) {
            info->playing = parsed_info->playing;
        }
    } else {
        rec = send_to_server(con, to_send);
        parsed_info = decode_data(rec, con->is_host);
        info->p1Pos = parsed_info->p1Pos;
        info->ballPos[0] = parsed_info->ballPos[0];
        info->ballPos[1] = parsed_info->ballPos[1];
        info->score[0] = parsed_info->score[0];
        info->score[1] = parsed_info->score[1];
        if (parsed_info->playing >= 0 || parsed_info->playing <= 2) {
            info->playing = parsed_info->playing;
        }
    }
    return info;
}

void end_con(ConInfo* con) {
    if(con) {
        free(con);
    }
}