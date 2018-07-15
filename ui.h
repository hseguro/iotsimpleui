#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netdb.h>

const int DEFAULT_PORT = 540;

class IoTUI{
    public:
        bool Init();
        void Background(short r, short g, short b);
        void Close();
        void Send(const char* msg);
    private:
        int sock;
        struct sockaddr_in server;
};

bool IoTUI::Init(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return false;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(DEFAULT_PORT);

    int connection_result = connect(sock, (struct sockaddr *)&server, sizeof(server));

    if(connection_result < 0){
        return false;
    }

    char buffer[256];

    int msg_result = read(sock, buffer, 255);
    if(msg_result < 0){
        printf("Error reading from socket\n");
    }
    printf("'%s'\n", buffer);

    return true;
}

void IoTUI::Send(const char* msg){
    write(sock, msg, sizeof(msg));
}

void IoTUI::Close(){
    //close(sock);
}