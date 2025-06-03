#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){

    char *ip = "127.0.0.1";
    int port = 6532;
    int n ;
    int server_sock,client_sock;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_size ;
    char buffer[1024];

    server_sock = socket(AF_INET,SOCK_DGRAM,0);
    if(server_sock<0){
        printf("[-] socket failed\n");
        exit(1);
    }
    printf("[+] Server socket established");
    
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        printf("[-] bind error\n");
        exit(1);
    }
    bzero(buffer,1024);
    addr_size = sizeof(client_addr);
    recvfrom(server_sock,buffer,1024,0,(struct sockaddr*)&client_addr,&addr_size);
    printf("[+] Data recieved from client:  %s\n",buffer);

    bzero(buffer,1024);
    strcpy(buffer,"Server send you a hii ");
    sendto(server_sock,buffer,1024,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    printf("[+] Data send successfully %s\n",buffer);



    return 0;

    


}