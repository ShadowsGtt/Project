#include "../include/wechat.h"
#include "../include/database.h"

void analysis_head(int fd)
{
    mesg_t mesg;
    char ch;
    Recv(fd,&ch,1,MSG_OOB);
    if(ch == 248)
        heart_count[fd] = 0;
    else
        Recv(fd,&mesg,sizeof(mesg_t),0);

}
