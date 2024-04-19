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
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof(serverAddr);
    
    while(1)
    {
        printf("Enter the message: ");
        fgets(buffer, sizeof(buffer), stdin);
        printf("Message sent to server\n");
        
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &serverAddr, addr_size);
        
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &serverAddr, &addr_size);
        printf("Reply from server: %s\n", buffer);
    }
    
    return 0;
}

