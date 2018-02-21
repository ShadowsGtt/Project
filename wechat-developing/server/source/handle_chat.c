#include "../include/wechat.h"
#include "../include/database.h"


void handle_chat(int fd)
{
    /* 提取头部 */
    struct 
    {
       int length;
       char src_name[16];
       char dst_name[16];
    }mesg;
    int n = recv(fd,&mesg,sizeof(mesg),0  );
    if(n == -1)
        perror("in handle_chat,recv");
    if(n == 0)
        close(fd);

    /* 转发内容 */
    int pipefd[2];
    n = pipe(pipefd);
    if(n == -1)
        perror("in handle_chat,pipefd");
    
    /* 消息移动到管道中 */
    splice(pipefd[1],NULL,fd,NULL,32768,0);
    get_fd_byname(mesg.dst_name);
}
