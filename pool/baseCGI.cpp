#include<sys/socket.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<libgen.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0])); //basename:返回不含路径的文件字符串
        return 1;
    }

    const char* ip = argv[1];
    int port = argv[2];

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PE_INET, SOCK_STREAM, 0);
    assert (sock >= 0);

    int ret = bind(sock, (struct sockaddr*)address, sizeof(address));
    assert(ret != -1);
    
    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);

    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);

    if (connfd < 0)
    {
        printf("erron");
    }  
    else{
        //dup函数：创建一个新的文件描述符，该文件描述符和原有的文件描述符指向相同的文件、管道或网络连接。
        close(STDOUT_FILENO);//关闭标准输出文件描述符，其值为1
        dup(connfd);//dup返回的文件描述符总是取系统当前可用的最小整数值，所以这里会取到1
        printf("abcd\n");
        close(connfd);
    }

    close(sock);
    return 0;
}
