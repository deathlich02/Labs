#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define SHIFT 4  // The encryption key (shift value)

void decrypt_message(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        if ((message[i] >= 'a' && message[i] <= 'z') || (message[i] >= 'A' && message[i] <= 'Z')) {
            message[i] -= SHIFT;
        }
    }
}

int main() {
    int sockfd, newsockfd, len, n;
    struct sockaddr_in server_addr, client_addr;
    char buf[256];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("SERVER: Socket creation error");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10200);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("SERVER: Bind error");
        exit(1);
    }

    // Listen for connections
    listen(sockfd, 5);
    printf("Server waiting for connection...\n");

    len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
    if (newsockfd < 0) {
        perror("SERVER: Accept error");
        exit(1);
    }

    // Receive encrypted message
    memset(buf, 0, sizeof(buf));
    n = read(newsockfd, buf, sizeof(buf));
    if (n < 0) {
        perror("SERVER: Read error");
        exit(1);
    }

    printf("Received encrypted message: %s\n", buf);

    // Decrypt message
    decrypt_message(buf);
    printf("Decrypted message: %s\n", buf);

    // Send decrypted message back to client
    write(newsockfd, buf, strlen(buf));

    // Close connections
    close(newsockfd);
    close(sockfd);

    return 0;
}
