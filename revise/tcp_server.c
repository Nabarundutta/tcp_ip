#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    char *ip = "127.0.0.1";
    int port = 6000;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    // 1. Create TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    // 2. Bind address to socket
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;  // convert port to network byte order
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0) {
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to the port number %d\n", port);

    // 3. Listen
    listen(server_sock, 5);
    printf("Listening ...\n");

    // 4. Accept loop
    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        if (client_sock < 0) {
            perror("[-]Accept error");
            continue;
        }

        printf("[+]Client connected from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 5. Receive data
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client says: %s\n", buffer);

        // 6. Send response
        bzero(buffer, 1024);
        strcpy(buffer, "Hi, this is server. Have a nice day!");
        send(client_sock, buffer, strlen(buffer), 0);

        // 7. Close client socket
        close(client_sock);
        printf("[-]Client disconnected.\n");
    }

    close(server_sock);
    return 0;
}
