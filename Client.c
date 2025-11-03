// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// //#include <unistd.h>
// //#include <sys/types.h>
// //#include <sys/socket.h>
// //#include <netinet/in.h>
// #include <winsock2.h>
// #include <ws2tcpip.h>
// // #include <netdb.h>

// void error(const char *msg){
//     perror(msg); //takes in error number and outputs error msg
//     exit(1);
// }

// int main(int argc, char *argv[]){
//     int sockfd, portno, n;
//     struct sockaddr_in serv_addr;
//     struct hostent *server;

//     char buffer[255];
//     if(argc < 3){
//         fprintf(stderr, "usage %s hostname port\n", argv[0]);
//         exit(1);
//     }
//     portno = atoi(argv[2]);
//     sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if(sockfd < 0)
//         error("ERROR opening socket");

//         server = gethostbyname(argv[1]);
//         if(server == NULL){
//             fprintf(stderr, "Error, no such host");

//             bzero((char *) &serv_addr, sizeof(serv_addr));
//             serv_addr.sin_family = AF_INET;
//             bcopy((char *) server->h_addr , (char*) &serv_addr.sin_addr.s_addr, server->h_length);
//             serv_addr.sin_port = htons(portno);
//             if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
//                 error("Connection failed");

//             while(1)
//             {
//                 bzero(buffer, 255);
//                 fgets(buffer, 255, stdin);
//                 n = write(sockfd, buffer, strlen(buffer));
//                 if(n < 0)
//                     error("Error on writing");
//                 bzero(buffer, 255);
//                 n = read(sockfd, buffer, 255);
//                 if(n < 0)
//                     error("Error on reading");
//                 pritf("Server: %s", buffer);

//                 int i = strncmp("Bye", buffer, 3);
//                 if(i == 0)
//                 break;
//             }
//         }
//         close(sockfd);
//         return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

void error(const char *msg) {
    fprintf(stderr, "%s: %d\n", msg, WSAGetLastError());
    exit(1);
}

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[255];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("WSAStartup failed");
    }

    if (argc < 3) {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        WSACleanup();
        exit(1);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed");
    }

    while (1) {
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);

        n = send(sockfd, buffer, strlen(buffer), 0);
        if (n == SOCKET_ERROR) {
            error("Error on writing");
        }

        memset(buffer, 0, 255);
        n = recv(sockfd, buffer, 255, 0);
        if (n == SOCKET_ERROR) {
            error("Error on reading");
        }
        printf("Server: %s", buffer);

        if (strncmp("Bye", buffer, 3) == 0) {
            break;
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
