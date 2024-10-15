#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void removeDuplicates(char* input, char* result) {
    char *word, *token;
    int wordCount[BUFFER_SIZE] = {0}; 
    char words[BUFFER_SIZE][BUFFER_SIZE]; 
    int wordIndex = 0, isDuplicate;

    word = strtok(input, " ");
    while (word != NULL) {
        isDuplicate = 0;
        for (int i = 0; i < wordIndex; i++) {
            if (strcmp(word, words[i]) == 0) {
                isDuplicate = 1;
                wordCount[i]++; 
                break;
            }
        }

        if (!isDuplicate) {
            strcpy(words[wordIndex], word);
            wordCount[wordIndex] = 1;
            wordIndex++;
        }

        word = strtok(NULL, " ");
    }

    result[0] = '\0';
    for (int i = 0; i < wordIndex; i++) {
        strcat(result, words[i]);
        strcat(result, " ");
    }

    result[strlen(result) - 1] = '\0';
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char result[BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for connections...\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        memset(result, 0, BUFFER_SIZE);

        read(new_socket, buffer, BUFFER_SIZE);
        printf("Message from client: %s\n", buffer);

        if (strcmp(buffer, "Stop") == 0) {
            printf("Terminating server.\n");
            break;
        }

        removeDuplicates(buffer, result);

        send(new_socket, result, strlen(result), 0);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}