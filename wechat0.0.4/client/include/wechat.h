#ifndef _GT_H
#define _GT_H

#define ServPort 40009
#define ServIp "127.0.0.1"
//#define ServIp "111.230.171.212"

#define MAXMESGLEN 100 /* 用户消息长度 */

/* 请求号 */
#define SIGNIN 5
#define SIGNUP 6
#define CHAT 7
#define GETFRITAB 8
#define ADDFRI 9


/* 请求结果 */
#define RADDFRI 50

pthread_t tid;

char username[16];

int sockfd;

void *thread_read(void *);

int Socket(int);         /* 根据参数创建相应套接字 */

void sig_chld(int);      /* 处理SIG_CHLD信号 */

int open_noblock(int);   /* 设置文件描述符为非阻塞,返回旧设置 */

void Getsockname(int ,struct sockaddr *,socklen_t *);  //获取内核赋予的ip和端口

int sign_in(int);

int sign_up(int);

void LoginMenu();

void get_password(char * const);

void get_fritab(int );

void running();

void friend_talk(int);

void res_add_friend(int);

void group_talk(int);

void main_page(int);

void manage_system(int);

void recv_add_fri(int);

void chat_system(int);

void recv_fri_mesg(int);

void add_friend(int);

void Connect();

void AllMenu();
void FriendManageMenu(); //好友管理菜单
void GroupManageMenu(); //群管理菜单
void ChatMenu(); //聊天菜单
void MainMenu();
void ManageMenu();
void friend_manage(int);

struct 
{
    char username[16];
    char pickname[16];
}fri_tab[50];

struct sockaddr_in serv_addr;
#endif
