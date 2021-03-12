/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Provides client's functions
*/



#include "online.h"

int connect_server(const char* address) {
    int sock;
    struct sockaddr_in serv_addr;
    char addr_in[INET_ADDRSTRLEN];
    sock = -1; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("[-] Error creating socket  \n"); 
        return sock; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    strcpy(addr_in, address);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {  
        printf("[-] Connection failed \n"); 
        return sock; 
    }
    return sock;
}

char* send_to_server(ConInfo* con, char* to_send) {
    char buffer[1024];
    char* b_ptr;
    send(con->socket , to_send , strlen(to_send) , 0 ); 
    read( con->socket , buffer, 1024); 
    b_ptr = buffer;
    return b_ptr;
}