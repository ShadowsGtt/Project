#include "../include/head.h"
#include "../include/wechat.h"

void * thread_read(void *fileno)
{
    int fd = *(int *)fileno;
    
    struct 
    {
        int type;  //消息类型
        int length;
        char src_name[16];
        char dst_name[16];
        char msg[MAXMESGLEN];
    }mesg;
    bzero(&mesg,sizeof(mesg));
    
    char file_name[35] = {0};
    int file_fd ;

    fd_set rset;
    FD_ZERO(&rset);
    
    
    for( ; ;)
    {
        FD_SET(fd,&rset);
        int res = select(fd+1,&rset,NULL,NULL,NULL);
        
        if(res == -1)
        { 
            if(errno == EINTR)
                continue;
            else
                perror("select");
        }

        if(FD_ISSET(fd,&rset))
        {
            int n = recv(fd,&mesg,sizeof(mesg),0);
            switch(mesg.type)
            {
                case CHAT:
                /* 将消息记录文件 */
                    sprintf(file_name,"WITH-%s",mesg.src_name);
                    file_fd = open(file_name,O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);
                    if(fd == -1)
                        perror("open");
                    int n = write(file_fd,&mesg.msg,sizeof(mesg.msg));
                    if(n == -1)
                        perror("write in file");
                /* 显示消息内容 */
    //printf("\033[;31m*************\033[0m");
                    printf("-------------------------------------\n");
                    printf("|              新消息               |\n");
                    printf("-------------------------------------\n");
                    
                    fprintf(stdout,"%s:%s\n",mesg.src_name,mesg.msg);
                    
                    break;
            }
        }

    }

}
