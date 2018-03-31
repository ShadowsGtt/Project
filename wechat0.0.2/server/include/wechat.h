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


#define BACKLOG 100
#define ServPort 40009
#define MAX_CONN 50000  //服务器最大连接数量
#define MAXMESGLEN  100 //用户消息最大长度

#define ServIp "0.0.0.0"
#define UDPSERV 1
#define UDPCLIENT 2
#define TCPSERV 3
#define TCPCLIENT 4

/* 客户端请求 */
#define SIGNIN 5
#define SIGNUP 6
#define CHAT 7
#define GETFRITAB 8
#define ADDFRI 9
#define RADDFRI 50
#define COUNT 5


/* 所有客户fd最大值 */
unsigned maxfd;

/* 记录所有客户fd */
unsigned int sockfd_set[MAX_CONN*5];

/* 记录客户端未回心跳的次数 */
char heart_count[MAX_CONN*5];

MYSQL *CONN_MYSQL;
//int epollfd;
//void (*prequest_func[MAX_CONN])(int);   
/* 指向处理请求函数的指针数组 */

/* 一个线程的定义 */
typedef struct  
{
    pthread_t tid;
    int pipe[2];
}thread_t;

thread_t thread[COUNT];

/* 消息包头 */
typedef struct
{
    unsigned short  type;
    unsigned short  length;
    unsigned int    seq;
    char            sour;
    char            dest;
}mesg_t;

/* 客户请求结果 */
typedef struct
{
    unsigned short  type;
    unsigned short  length;
    unsigned int    seq;
}mesg_res_t;


/* 在线客户信息结构体 */
struct
{
    int fd;
    char username[16];      //用户名
    char pickname[20];      //昵称
}clients_mesg[MAX_CONN];


extern int Socket(int);         /* 根据参数创建相应套接字 */

extern void sig_chld(int);      /* 处理SIG_CHLD信号 */

extern int open_noblock(int);   /* 设置文件描述符为非阻塞,返回旧设置 */

extern int set_daemon(const char*,int); /* 设置当前进程为守护进程,第一个参数为程序名字(argv[0]),第二个是设施,成功返回0  */

extern void Getsockname(int ,struct sockaddr *,socklen_t *);  //获取内核赋予的ip和端口

extern void main_thread_func(); 

extern void handle_connection(int);

extern void analysis_head(int);

extern void register_epoll_fd(int epollfd,int fd,int oneshot);

extern void handle_read_request(int);

extern void handle_sign_in(int);

extern void handle_sign_up(int);

extern void handle_chat(int);

extern void handle_get_fritab(int);

extern void handle_add_fri(int);

extern void handle_radd_fri(int);

extern void *thread_run(void *);

extern void create_work_thread(int);

extern ssize_t Recv(int,void *,size_t,int);

extern ssize_t Send(int,void *,size_t,int);

/* 心跳线程运行的函数 */
extern void *heart_beat(void *);

extern int get_fd_byname(const char *);

extern ssize_t splice(int fd_in, loff_t *off_in, int fd_out,
                      loff_t *off_out, size_t len, unsigned int flags);

extern void handle_get_fritab(int);
struct sockaddr_in serv_addr;
//struct sockaddr_in client_addr;
#endif
