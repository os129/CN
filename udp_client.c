#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Communicate with the server
    while (1) {
        // Get input from the user
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        // Send message to server
        sendto(sock_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);
        printf("Message sent to server\n");

        // If user types 'exit', terminate the communication
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting the client...\n");
            break;
        }

        // Receive response from server
        int n = recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        buffer[n] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    // Close the socket
    close(sock_fd);
    return 0;
}

