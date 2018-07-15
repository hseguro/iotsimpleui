#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "utils/framebuffer.h"

//#define _DEBUG_

using namespace std;

int MAIN_PORT = 540;
int INTERACTION_SERVER = 545;
bool running = true;
int sockfd;
socklen_t clilen;
char buffer[1024*2];
struct sockaddr_in server, client;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//#define _DEBUG_

int main(int argc, char const *argv[]){
    if(argc > 2){
        #ifdef _DEBUG_
        printf("Arguments: %d\n", argc-1);
        #endif
        for(int i = 1; i < argc; i+=2){
            auto key = argv[i];
            auto value = argv[i+1];
            #ifdef _DEBUG_
            printf("Key: %s\n", key);
            #endif
            if(strcmp(key, "-p") == 0){
                MAIN_PORT = stoi(value);
                INTERACTION_SERVER = MAIN_PORT + 5;
                #ifdef _DEBUG_
                printf("Port: %d\n", stoi(value));
                #endif
            }else if(strcmp(key, "-device") == 0){
                #ifdef _DEBUG_
                printf("Framebuffer device: %s\n", value);
                #endif
            }
        }
    }else{
        //All default
        #ifdef _DEBUG_
        printf("None argument. setting all default\n");
        #endif
        
    }

    Framebuffer fb = Framebuffer();

    if(fb.Init() == -1){
        error("ERROR opening frambebuffer");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        error("ERROR opening socket");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(540);

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server))){
        error("ERROR binding");
    }

    listen(sockfd, 5);
    puts("Waiting connections...");

    while(running){
        int c = sizeof(struct sockaddr_in);
        int clientfd = accept(sockfd, (struct sockaddr *)&client, (socklen_t*)&c);

        if(clientfd < 0){
            error("ERROR accept client");
        }

        printf("server: got connection from %s port %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        send(clientfd, "Hello, World!", 15, 0);
    }
}