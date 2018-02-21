#include "../include/head.h"
#include "../include/wechat.h"

void get_fritab(int fd)
{
    struct 
    {
        int type;
        int length;

    }mesg = {GETFRITAB,0};
    
    
    int n = send(fd,&mesg,sizeof(mesg),0);
    if(n  == -1)
        perror("send in get_fritab");
    n = recv(fd,fri_tab,sizeof(fri_tab),0);
    if(n == -1)
        perror("recv in get_fritab");
}
