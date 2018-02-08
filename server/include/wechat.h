#ifndef _GT_H
#define _GT_H
#include<netdb.h>
#include<wait.h>
#include<syslog.h>
#include <poll.h>
#include<signal.h>
#include<mysql.h>
#include <fcntl.h>
#include<sys/sendfile.h>
#include<pthread.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/epoll.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include<sys/select.h>


#define BACKLOG 100
#define ServPort 40009
#define MAX_CONN 50000  //服务器最大连接数量

#define ServIp "0.0.0.0"
#define UDPSERV 1
#define UDPCLIENT 2
#define TCPSERV 3
#define TCPCLIENT 4

/* 客户端请求 */
#define SIGNIN 5
#define SIGNUP 6
#define ADDFRID 7
#define DELFRID 8
#define SDMESG 9




int num ;

MYSQL *CONN_MYSQL;
int epollfd;
void (*prequest_func[MAX_CONN])(int);   /* 指向处理请求函数的指针 */


struct friends
{
    char username[16];
    char beizhu[20];
};

/* 在线客户信息结构体 */
struct clients
{
    int fd;
    char username[16];      //用户名
    char pickname[20];      //昵称
    struct friends online_friends[20]; //好友
}clients_msg[MAX_CONN];


extern int Socket(int);         /* 根据参数创建相应套接字 */

extern void sig_chld(int);      /* 处理SIG_CHLD信号 */

extern int open_noblock(int);   /* 设置文件描述符为非阻塞,返回旧设置 */

extern int set_daemon(const char*,int); /* 设置当前进程为守护进程,第一个参数为程序名字(argv[0]),第二个是设施,成功返回0  */

extern void Getsockname(int ,struct sockaddr *,socklen_t *);  //获取内核赋予的ip和端口

extern void main_thread_func(); 

extern void handle_connection(int);

extern void register_epoll_fd(int epollfd,int fd,int oneshot);

extern void handle_read_request(int);

extern void handle_sign_in(int);

extern void handle_sign_up(int);

//int select_result(MYSQL *,const char *);

struct sockaddr_in serv_addr;
//struct sockaddr_in client_addr;
#endif
