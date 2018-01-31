#ifndef _GT_H
#define _GT_H
#include<netdb.h>
#include<wait.h>
#include<syslog.h>
#include <poll.h>
#include<signal.h>
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
#define MAX_USER_MSG  100 //用户最大发送消息大小
#define BACKLOG 100
#define ServPort 40009
#define MAX_CONN 50000  //服务器最大连接数量
#define MAX_THREADS 64
#define MAX_QUEUE 65536
#define LocalIp "127.0.0.1"
#define ServIp "127.0.0.1"
#define UDPSERV 1
#define UDPCLIENT 2
#define TCPSERV 3
#define TCPCLIENT 4
#define SIGNIN 5
#define SIGNUP 6

int num ;

int epollfd;
//int epollfd = epoll_create(MAX_CONN);   //创建epoll文件描述符
void (*prequest_func[MAX_CONN])(int);   /* 指向处理请求函数的指针 */


/**
 * 线程池关闭的方式
 */
typedef enum {
    immediate_shutdown = 1,
    graceful_shutdown  = 2
} threadpool_shutdown_t;

/**
 * 线程池一个任务的定义
 */
typedef struct 
{
    void (*function)(int);
    //void *argument;
    int argument;
}threadpool_task_t;

/* 客户请求头部结构体 */
typedef struct
{
    int request_id;                 /* 请求号     */
    char  to[16];                   /* 消息目的地用户名 */
    char  from[16];                 /* 消息来源用户名   */

}request_t;

typedef struct 
{
    int from_fd;
    int to_fd;
    int pipefd[2];
}handle_request_t;


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

/* 线程参数 */
typedef struct
{
    int epollfd;
    int listenfd;    
    int sockfd;     //发出消息者描述符
}thread_arg_t;


/* 定义错误码 */
typedef enum {
    threadpool_invalid        = -1,
    threadpool_lock_failure   = -2,
    threadpool_queue_full     = -3,
    threadpool_shutdown       = -4,
    threadpool_thread_failure = -5
} threadpool_error_t;

typedef enum {
    threadpool_graceful       = 1
} threadpool_destroy_flags_t;


typedef struct threadpool 
{
  pthread_mutex_t lock;     //互斥锁
  pthread_cond_t notify;    //线程等待的条件变量
  pthread_t *threads;       //指向线程数组的
  threadpool_task_t *queue; //指向任务队列头的指针
  int thread_count;         //线程数量
  int queue_size;           //任务数量最大值
  int head;                 //任务队列头
  int tail;                 //任务队列尾
  int count;                //已经存在的任务数量
  int shutdown;             //标记线程迟是否关闭
  int started;              //线程池现有线程数量
}threadpool_t;

extern int Socket(int);         /* 根据参数创建相应套接字 */
extern void sig_chld(int);      /* 处理SIG_CHLD信号 */
extern int open_noblock(int);   /* 设置文件描述符为非阻塞,返回旧设置 */
extern int set_daemon(const char*,int); /* 设置当前进程为守护进程,第一个参数为程序名字(argv[0]),第二个是设施,成功返回0  */
extern void Getsockname(int ,struct sockaddr *,socklen_t *);  //获取内核赋予的ip和端口

extern void *threadpool_thread(void *);

extern int threadpool_free(threadpool_t *);

extern threadpool_t *threadpool_create(int , int , int);

extern int threadpool_add(threadpool_t *, void (*)(int),int , int );

extern void main_thread_func(); 

extern int threadpool_destroy(threadpool_t *pool, int flags);

extern void handle_connection(int);

extern void register_epoll_fd(int epollfd,int fd,int oneshot);

extern void handle_read_request(int);

extern void handle_write_request(int);

extern void handle_sign_in(int);

extern void handle_sign_up(int);

struct sockaddr_in serv_addr;
//struct sockaddr_in client_addr;
#endif
