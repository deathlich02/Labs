#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORTNO 10200
#define MAX_SIZE 256

int main() {
    int sockfd, newsockfd, clilen;
    char buf[MAX_SIZE];
    struct sockaddr_in seraddr, cliaddr;
    time_t current_time;
    char *time_str;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY; // Accept connections on any interface
    seraddr.sin_port = htons(PORTNO);

    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd, 5);
    printf("Daytime Server is waiting for connections...\n");

    while (1) {
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            continue;
        }

        if (fork() == 0) {
            // Child process
            close(sockfd); // Close the listening socket in the child process

            // Get the current time
            current_time = time(NULL);
            if (current_time == ((time_t)-1)) {
                perror("ERROR getting time");
                exit(1);
            }

            // Convert time to a readable format
            time_str = ctime(&current_time);
            if (time_str == NULL) {
                perror("ERROR converting time");
                exit(1);
            }

            // Send the current time to the client
            write(newsockfd, time_str, strlen(time_str));

            // Send the process ID
            int pid = getpid();
            write(newsockfd, &pid, sizeof(pid));

            close(newsockfd);
            exit(0);
        } else {
            close(newsockfd); // Parent process closes the client socket
        }
    }

    return 0;
}
