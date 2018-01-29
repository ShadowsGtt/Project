#ifndef _WECHAT_H
#define _WECHAT_H
#include<netdb.h>
#include <poll.h>
#include<sys/sendfile.h>
#include <mysql.h>
#include<pthread.h>
#include <errmsg.h>
#include <mysqld_error.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include<sys/select.h>
#include<sys/epoll.h>
#include <fcntl.h>
#define BACKLOG 100
#define ServPort 40009
#define MaxClients 500
#define LocalIp "127.0.0.1"
#define ServIp "localhost"

#endif
