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

void encrypt_message(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        if ((message[i] >= 'a' && message[i] <= 'z') || (message[i] >= 'A' && message[i] <= 'Z')) {
            message[i] += SHIFT;
        }
    }
}

int main() {
    int sockfd, len, result;
    struct sockaddr_in address;
    char message[256], buf[256];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("CLIENT: Socket creation error");
        exit(1);
    }

    // Server address configuration
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(10200);
    len = sizeof(address);

    // Connect to server
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("CLIENT: Connection error");
        exit(1);
    }

    // Get input message
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline

    // Encrypt message
    encrypt_message(message);
    printf("Encrypted message: %s\n", message);

    // Send encrypted message to the server
    write(sockfd, message, strlen(message));

    // Receive the processed message from server
    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("Server response: %s\n", buf);

    // Close the socket
    close(sockfd);

    return 0;
}

