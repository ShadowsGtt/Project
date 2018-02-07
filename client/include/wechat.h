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
#include<curses.h>
#define ServPort 40009
#define ServIp "127.0.0.1"
#define UDPCLIENT 2
#define TCPCLIENT 4
#define SIGNIN 5
#define SIGNUP 6

int Socket(int);         /* 根据参数创建相应套接字 */

void sig_chld(int);      /* 处理SIG_CHLD信号 */

int open_noblock(int);   /* 设置文件描述符为非阻塞,返回旧设置 */

void Getsockname(int ,struct sockaddr *,socklen_t *);  //获取内核赋予的ip和端口

int sign_in(int);

int sign_up(int);

void LoginMenu();


struct sockaddr_in serv_addr;
#endif
