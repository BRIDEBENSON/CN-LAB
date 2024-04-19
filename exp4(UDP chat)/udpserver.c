#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2000);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    
    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    printf("Listening...\n");
    
    addr_size = sizeof(serverAddr);
    
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &serverAddr, &addr_size);
        printf("Received message from client: %s\n", buffer);
        
        printf("Enter the message: ");
        fgets(buffer, sizeof(buffer), stdin);
        printf("Message sent to client\n");
        
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &serverAddr, addr_size);
    }
    
    return 0;
}

