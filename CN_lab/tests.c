#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void sort_array(int *arr, int n) {
    int temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pid_t child_pid;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
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
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept");
            exit(EXIT_FAILURE);
        }
        child_pid = fork();

        if (child_pid == 0) {
            close(server_fd);

            int n, arr[BUFFER_SIZE];
            char result[BUFFER_SIZE] = {0};
            read(new_socket, &n, sizeof(int));
            read(new_socket, arr, n * sizeof(int));
            sort_array(arr, n);
            pid_t pid = getpid();
            snprintf(result, BUFFER_SIZE, "Sorted Array: ");
            for (int i = 0; i < n; i++) {
                char temp[10];
                snprintf(temp, sizeof(temp), "%d ", arr[i]);
                strcat(result, temp);
            }

            char pid_message[50];
            snprintf(pid_message, sizeof(pid_message), "\nProcess ID: %d", pid);
            strcat(result, pid_message);
            send(new_socket, result, strlen(result), 0);
            close(new_socket);
            exit(0);
        } else if (child_pid > 0) {
            close(new_socket);
            wait(NULL);
        } else {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}