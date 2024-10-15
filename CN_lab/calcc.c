#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>

#define PORTNO 8080
int main()
{
    int sockfd,n1,n2,result;
    char operator;
    struct sockaddr_in address;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = inet_addr("192.168.73.201");
    connect(sockfd,(struct sockaddr*)&address,sizeof(address));

    printf("Enter the numbers: \n");
    scanf("%d %d",&n1,&n2);
    printf("Enter the operator: \n");
    scanf(" %c",&operator);
    n1 = htonl(n1);
    n2 = htonl(n2);

    send(sockfd,&n1,sizeof(int),0);
    send(sockfd,&n2,sizeof(int),0);
    send(sockfd,&operator,sizeof(char),0);

    read(sockfd,&result,sizeof(int));
    result = ntohl(result);
    printf("The result is: %d \n", result);
    close(sockfd);
    return 0;
}