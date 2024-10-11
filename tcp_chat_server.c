#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Chat loop
    while (1) {
        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Read message from client
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread == 0) {
            printf("Client disconnected\n");
            break;
        }
        printf("Client: %s\n", buffer);

        // Check if client wants to exit
        if (strcmp(buffer, "exit") == 0) {
            printf("Client has exited the chat.\n");
            break;
        }

        // Get server response
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        // Send response to client
        write(new_socket, buffer, strlen(buffer));

        // Exit if server sends "exit"
        if (strcmp(buffer, "exit") == 0) {
            printf("Server has exited the chat.\n");
            break;
        }
    }

    // Close the socket
    close(new_socket);
    close(server_fd);
    return 0;
}
