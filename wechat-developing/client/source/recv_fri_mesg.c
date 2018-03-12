
#include "../include/head.h"
#include "../include/wechat.h"

void recv_fri_mesg(int fd)
{
    //printf("-------------in recv_fri_mesg--------------------\n");
    struct 
    {
        char dst_name[16];
        char src_name[16];
        char mesg[MAXMESGLEN];
    }mesg;

    int n = recv(fd,&mesg,sizeof(mesg),0 );
    if(n == -1)
        perror("recv in recv_fri_mesg");
    printf("\n---------------新消息----------------\n");
    printf("好友[%s]:%s\n",mesg.src_name,mesg.mesg);
    printf("----------------------------------------\n");
    bzero(&mesg,sizeof(mesg));
    
}
