/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Provides functions to encode/decode data to send /received
*/

#include "online.h"


char* encode_data(SharedInfo* info, int is_host) {
    char *res;

    res = malloc(sizeof(char) * 1024);
    if(is_host == 1) {
        sprintf(res, "{\"pos_p1\": %d, \"pos_p2\": %d, \"ball\": [%d, %d], \"score\": [%d, %d], \"playing\": %d }",
         info->p1Pos,info->p2Pos, info->ballPos[0], info->ballPos[1], info->score[0], info->score[1], info->playing);
    } else {
        sprintf(res, "{\"pos_p2\": %d, \"playing\": %d }", info->p2Pos, info->playing);
    }

    return res;
}


SharedInfo* decode_data(const char* data, int is_host) {
    SharedInfo* res;
    res = malloc(sizeof(*res));

    cJSON *json = cJSON_Parse(data);
    if (is_host == 1) {
        cJSON *posP2, *playing;
        // Get back onluy P2 pos
        posP2 = cJSON_GetObjectItemCaseSensitive(json, "pos_p2");
        if (cJSON_IsNumber(posP2)) {
            res->p2Pos = posP2->valueint;        
        }
        playing = cJSON_GetObjectItemCaseSensitive(json, "playing");

        if (cJSON_IsNumber(playing)) {
            res->playing = playing->valueint;       
        }

    } else {
        cJSON *posP1, *playing, *ball, *score;
        posP1 = cJSON_GetObjectItemCaseSensitive(json, "pos_p1");
        if (cJSON_IsNumber(posP1)) {
            res->p1Pos = posP1->valueint;        
        }
        ball = cJSON_GetObjectItemCaseSensitive(json, "ball");
        for(int i = 0; i < cJSON_GetArraySize(ball); i++) {
            res->ballPos[i] = cJSON_GetArrayItem(ball, i)->valueint;
        }
        score = cJSON_GetObjectItemCaseSensitive(json, "score");
        for(int i = 0; i < cJSON_GetArraySize(score); i++) {
            res->score[i] = cJSON_GetArrayItem(score, i)->valueint; 
        }
        playing = cJSON_GetObjectItemCaseSensitive(json, "playing");
        if (cJSON_IsNumber(playing)) {
            res->playing = playing->valueint;        
        }
    }

    return res;
}