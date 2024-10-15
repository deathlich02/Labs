#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORTNO 10200
#define MAX_SIZE 256

int main() {
    int sockfd, n;
    struct sockaddr_in address;
    char buf[MAX_SIZE];
    int pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change this to your server IP
    address.sin_port = htons(PORTNO);

    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    // Receive the current date and time from the server
    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("Server Date and Time: %s\n", buf);

    // Receive the process ID from the server
    read(sockfd, &pid, sizeof(pid));
    printf("Server Process ID: %d\n", pid);

    close(sockfd);
    return 0;
}
