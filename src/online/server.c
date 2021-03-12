/*
** ETNA PROJECT, BACHELOR MARS 2023
** PONG
** author: barrie_p
** File description:
** 		Provides server's functions
*/


#include "online.h"

int run_server() {
    int server_fd; 
    int sock;
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("[-] Failed to create a socket"); 
        exit(EXIT_FAILURE);
        return -1;
    } 
    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("[-] Failed to attach the socket"); 
        exit(EXIT_FAILURE); 
        return -1;
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);
       
    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("[-] Failed to attach the socket");  
        exit(EXIT_FAILURE); 
        return -1;
    } 
    
    if (listen(server_fd, 3) < 0) { 
        perror("[-] An error occured when trying to listen");  
        exit(EXIT_FAILURE);
        return -1;
    } 
    if ((sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
        perror("[-] An error occured when trying to accept a connection");
        exit(EXIT_FAILURE);
        return -1;
    } 

    return sock;
}


char* serve(ConInfo* con, char* to_send) {
    char buffer[1024]; 
    char* b_ptr;

    read( con->socket , buffer, 1024); 
    send(con->socket , to_send , strlen(to_send) , 0); 

    b_ptr = buffer;
    return b_ptr;
}