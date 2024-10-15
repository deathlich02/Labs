#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PORTNO 8080

int ops(int n1,int n2,char operator)
{
    switch(operator)
    {
        case '+':
            return n1 + n2;
        case '-':
            return n1 - n2;
        case '*':
            return n1 * n2;
        case '/':
            return n1 / n2;
    }
}

int main()
{
    int sockfd,newsockfd,res;
    struct sockaddr_in seraddr,cliaddr;
    int len = sizeof(cliaddr);

    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8080);
    seraddr.sin_addr.s_addr = inet_addr("192.168.73.201");

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
    listen(sockfd,5);
    printf("Server is listening \n");
    while(1)
    {
        newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr, (socklen_t *)&len);
        pid_t child = fork();
        if(child == 0)
        {
            close(sockfd);
            int n1,n2;
            char operator;
            read(newsockfd,&n1,sizeof(int));
            read(newsockfd,&n2,sizeof(int));
            read(newsockfd,&operator,sizeof(char));

            n1 = ntohl(n1);
            n2 = ntohl(n2);
            int result = ops(n1,n2,operator);
            result = htonl(result);
            send(newsockfd,&result,sizeof(int),0);
            close(newsockfd);
            exit(0);
        }
        else if(child > 0)
        {
            close(newsockfd);
            wait(NULL);
        }
        else
        {
            perror("Failed \n");
            exit(0);
        }
    }
    return 0;
}