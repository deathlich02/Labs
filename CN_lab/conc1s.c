#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

void sort_array(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
} 

int main() {
    int sockfd, newsockfd, portno, clilen;
    char buf[MAX_SIZE];
    struct sockaddr_in seraddr, cliaddr;

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
    printf("Server is waiting for connections...\n");

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

            // Read array size
            int n;
            read(newsockfd, &n, sizeof(n));

            // Read the array
            int arr[MAX_SIZE];
            read(newsockfd, arr, n * sizeof(int));

            // Sort the array
            sort_array(arr, n);

            // Send back the sorted array
            write(newsockfd, arr, n * sizeof(int));

            // Send process ID
            int pid = getpid();
            write(newsockfd, &pid, sizeof(pid));

            close(newsockfd);
            exit(0);
        } else {
            close(newsockfd); // Close the socket in the parent process
        }
    }

    return 0;
}
