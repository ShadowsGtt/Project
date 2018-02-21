
#include "../include/wechat.h"
void handle_read_request(int fd)
{
    int request_id;
    int n = recv(fd,&request_id,4,0);
    if(n == -1)
    {
        char errobuf[20];
        sprintf(errobuf,"recv fd[%d]",fd);
        perror(errobuf);
    }
    if(n == 0)
    {
        printf("client close\n");
        close(fd);
        return;
    }
    printf("request_id:%d\n",request_id);
    switch(request_id)
    {
        /* 登录 */
        case SIGNIN:
            prequest_func[fd] = handle_sign_in;

            break;

         /* 注册 */   
        case SIGNUP:
            prequest_func[fd] = handle_sign_up;

            break;
        /* 聊天 */
        case CHAT:
            prequest_func[fd] = handle_chat;
        
            break;
        /*　请求好友表 */
        case GETFRITAB:
            prequest_func[fd] = handle_get_fritab;
        
            break;
    }
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLOUT | EPOLLET;
    //event.events |= EPOLLONESHOT;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }

}
