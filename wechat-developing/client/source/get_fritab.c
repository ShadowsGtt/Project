#include "../include/head.h"
#include "../include/wechat.h"

void get_fritab(int fd)
{
    struct 
    {
        int type;
    }mesg = {GETFRITAB};
    
    
    /* 请求获得好友表 */
    int n = send(fd,&mesg,sizeof(mesg),0);
    if(n  == -1)
        perror("send in get_fritab");

    /* 接收好友表 */
    n = recv(fd,fri_tab,sizeof(fri_tab),0);
    if(n == -1)
        perror("recv in get_fritab");
}
