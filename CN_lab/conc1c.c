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
    int sockfd, n;
    struct sockaddr_in address;

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

    // Input the number of elements in the array
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    // Send the size of the array to the server
    write(sockfd, &n, sizeof(n));

    // Input the array elements
    int arr[MAX_SIZE];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Send the array to the server
    write(sockfd, arr, n * sizeof(int));

    // Receive the sorted array from the server
    int sorted_arr[MAX_SIZE];
    read(sockfd, sorted_arr, n * sizeof(int));

    // Receive the process ID from the server
    int pid;
    read(sockfd, &pid, sizeof(pid));

    // Display the sorted array and the process ID
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", sorted_arr[i]);
    }
    printf("\nProcess ID of the server: %d\n", pid);

    close(sockfd);
    return 0;
}
