#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int sockid, len, row_count = 0;
    struct sockaddr_in seraddr, cliaddr;
    char buf[MAX];
    char matrix[ROWS][MAX];  // To store the rows of the matrix

    // Create UDP socket
    sockid = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockid < 0) {
        perror("Server: Socket creation failed");
        exit(1);
    }

    // Construct the server address
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.56.10");  // Replace with your IP
    seraddr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(sockid, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("Server: Bind failed");
        close(sockid);
        exit(1);
    }

    len = sizeof(cliaddr);

    // Receive rows of the matrix
    while (row_count < ROWS) {
        memset(buf, 0, MAX);
        int m = recvfrom(sockid, buf, MAX, 0, (struct sockaddr *)&cliaddr, &len);
        if (m < 0) {
            perror("Server: Receive failed");
            exit(1);
        }
        printf("Received row %d: %s\n", row_count + 1, buf);
        strcpy(matrix[row_count], buf);
        row_count++;
    }

    // Print the combined matrix
    printf("Complete matrix received:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", matrix[i]);
    }

    // Send acknowledgment back to the client
    char ack[] = "Matrix received successfully.";
    sendto(sockid, ack, sizeof(ack), 0, (struct sockaddr *)&cliaddr, len);

    // Close socket
    close(sockid);
    return 0;
}
