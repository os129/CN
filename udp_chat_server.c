#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Chat loop
    while (1) {
        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message from client
        int n = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
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
        sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len);

        // Exit if server sends "exit"
        if (strcmp(buffer, "exit") == 0) {
            printf("Server has exited the chat.\n");
            break;
        }
    }

    // Close the socket
    close(server_fd);
    return 0;
}
