#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    int sock, cli;
    struct sockaddr_in server, client;
    int len;
    char mesg[] = "Hello!\n";
    int sent;


    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8119);
    // lsof -Pn -i4 | grep 8117
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    len = sizeof(struct sockaddr_in);

    if((bind(sock, (struct sockaddr*)&server, len)) == -1)
    {
        perror("bind");
        return -1;
    }

    if((listen(sock, 5)) == -1)
    {
        perror("listen");
        return -1;
    }

    while(1)
    {
        if((cli = accept(sock, (struct sockaddr*)&client, (socklen_t*)&len)) == -1)
        {
            perror("accept");
            return -1;
        }

        sent = send(cli, mesg, strlen(mesg), 0);

        printf("Sent %d bytes to client : %s on port %d\n", sent, inet_ntoa(client.sin_addr), htons(client.sin_port));

        close(cli);

    }



    return 0;
}
