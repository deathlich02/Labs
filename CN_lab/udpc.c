#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 9704
#define MAX 256
#define ROWS 3  // Number of rows to send

int main() {
    int sockid, len;
    struct sockaddr_in address;
    char buf[MAX], ack[MAX];

    // Create UDP socket
    sockid = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockid < 0) {
        perror("Client: Socket creation failed");
        exit(1);
    }

    // Construct the server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.56.10");  // Replace with your IP
    address.sin_port = htons(PORT);

    len = sizeof(address);

    // Send rows of the matrix
    for (int i = 0; i < ROWS; i++) {
        printf("Enter row %d of the matrix: ", i + 1);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';  // Remove newline character

        // Send the row to the server
        int m = sendto(sockid, buf, sizeof(buf), 0, (struct sockaddr *)&address, len);
        if (m < 0) {
            perror("Client: Send failed");
            exit(1);
        }
    }

    // Receive acknowledgment from the server
    int n = recvfrom(sockid, ack, sizeof(ack), 0, (struct sockaddr *)&address, &len);
    if (n < 0) {
        perror("Client: Receive failed");
        exit(1);
    }
    printf("Server response: %s\n", ack);

    // Close socket
    close(sockid);
    return 0;
}
