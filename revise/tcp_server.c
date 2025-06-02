#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(){
    char *ip = "127.0.0.1";
    int port = 5565;

    // make the veraibles
    int server_sock,client_sock;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n ;

    // create the tcp socket
    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        perror("[-] Socket error");
        exit(1);
    }
    printf("[-] TCP server socket created");

    // Configure server address
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Bind the socket to the port 
    n = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if (n<0){
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+] Bind successfull at port : %d",port);


    listen(server_sock,5);
    printf("Server is listening: ");
    while(1){
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);
        printf("[+] Client connected.\n");
        bzero(buffer, 1024);  // Clear buffer
        recv(client_sock, buffer, sizeof(buffer), 0);  // Wait for client message
        printf("Client: %s\n", buffer);

        bzero(buffer, 1024);  // Clear buffer again
        strcpy(buffer, "hello this server have a nice day");  // Server response
        printf("Server: %s\n", buffer);
        send(client_sock, buffer, sizeof(buffer), 0);  // Send response
    }
    close(client_sock);
    printf("[+] Client disconnected\n\n");





    return 0;
}
