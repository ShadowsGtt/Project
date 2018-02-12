#ifndef _GT_H
#define _GT_H

#define ServPort 40009
#define ServIp "127.0.0.1"
//#define ServIp "111.230.171.212"
#define UDPCLIENT 2
#define TCPCLIENT 4
#define SIGNIN 5
#define SIGNUP 6

int sockfd;

int Socket(int);         /* 根据参数创建相应套接字 */

void sig_chld(int);      /* 处理SIG_CHLD信号 */

int open_noblock(int);   /* 设置文件描述符为非阻塞,返回旧设置 */

void Getsockname(int ,struct sockaddr *,socklen_t *);  //获取内核赋予的ip和端口

int sign_in(int);

int sign_up(int);

void LoginMenu();

void get_password(char * const);

void running();

void friend_talk(int);

void group_talk(int);

void main_page(int);

void manage_system(int);

void chat_system(int);

extern void Connect();

extern void AllMenu();
extern void FriendManageMenu(); //好友管理菜单
extern void GroupManageMenu(); //群管理菜单
extern void ChatMenu(); //聊天菜单
extern void MainMenu();


struct sockaddr_in serv_addr;
#endif
