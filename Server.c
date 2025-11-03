#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <winsock2.h>
#include <ws2tcpip.h>

void error(const char *msg){
    perror(msg); //takes in error number and outputs error msg
    exit(1);
}

int main(int argc, char *argv[]) // argc = total number of parameters and argv = contains original parameters - here, file and port number
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }


    if(argc < 2){
        fprintf(stderr , "Port number not provided. Program terminated \n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[255]; //used to store msgs and transfer it in the form of data streams

    // sockaddr_in - gives us internet address -> included in file netinet.in.h
    struct sockaddr_in serv_addr, cli_addr; // so basically we want internet address of server-serv_addr and client-cli_addr
    socklen_t clilen; //clilen-length of client address and socklen_t- datatype in server.h of 32 byte size

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0) // socket function results in failure
    {
        error("Error opening socket.");
    }

    //bzero((char *) &serv_addr , sizeof(serv_addr)); // clears data or text - here, we are clearing content inside serv_addr
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Binding
    if(bind(sockfd, (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0){
        error("Binding failed.");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr , &clilen);

    if(newsockfd < 0)
    error("Error on Accept");

    while(1){
        memset(buffer, 0, 255); // make buffer empty
        n = recv(newsockfd, buffer, 255, 0);
        if(n < 0)
            error("Error on Reading");
        printf("Client: %s\n", buffer);
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);  // reads streams of input

        n = send(newsockfd, buffer, strlen(buffer), 0);
        if(n < 0)
            error("Error on Writing");
        int i = strncmp("Bye", buffer, 3);
        if(i == 0)
        break;
    }


    closesocket(newsockfd);
    closesocket(sockfd);
    // Close Winsock
    WSACleanup();
    return 0;
}
