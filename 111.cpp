/******************************************************************************
* client.c                                                                    *
*                                                                             *
* Description: 本文件是客户端C源代码，采用“./client 主机 端口” 访问服务器，比 *
*              如本机访问默认为“./client localhost 9999”                      *
*                                                                             *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

#define PORT 9000
#define BUF_SIZE 4096

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <server-ip> <port>",argv[0]);
        return EXIT_FAILURE;
    }

    char buf[BUF_SIZE];
        
    int status, sock;
    struct addrinfo hints;
    //将变量hints内存空间置空
	memset(&hints, 0, sizeof(struct addrinfo));
    struct addrinfo *servinfo; 
    hints.ai_family = AF_UNSPEC;  //协议无关，地址族可IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; //TCP流sockets
    hints.ai_flags = AI_PASSIVE; //地址处理方式，用于监听绑定
    //地址和端口等信息转换，存放到servinfo中
    if ((status = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(status));
        return EXIT_FAILURE;
    }
    //创建客户端套接字
    if((sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        fprintf(stderr, "Socket failed");
        return EXIT_FAILURE;
    }
    //向服务器发起连接请求，连接成功后，客户端通过sock套接字与服务器进行交互
    if (connect (sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        fprintf(stderr, "Connect failed/n");
        return EXIT_FAILURE;
    }
        
    char msg[BUF_SIZE];
    char *ex = "exit";
    fprintf(stdout, "输入数据(exit退出):");
    fgets(msg, BUF_SIZE, stdin);
   
    while(strncmp(msg,ex,4)){
      //等待用户的输入，并存入msg数组中，注意不要超过BUF_SIZE大小
      int bytes_received;
      fprintf(stdout, "Sent from client>>: %s", msg);

      //将输入信息通过sock套接字发送出去
      send(sock, msg , strlen(msg), 0);

      //接收服务器反馈回来的数据
      if((bytes_received = recv(sock, buf, BUF_SIZE, 0)) > 1)
	{
	  buf[bytes_received] = '\0';
	  fprintf(stdout, "Received from server<<: %s", buf);
	}
      fprintf(stdout, "输入数据(exit退出):");
      fgets(msg, BUF_SIZE, stdin);        
    }

    //释放空间，并关闭套接字
    freeaddrinfo(servinfo);
    close(sock);    
    return EXIT_SUCCESS;
}
