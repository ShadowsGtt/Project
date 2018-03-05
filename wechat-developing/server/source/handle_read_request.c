
#include "../include/wechat.h"
void handle_read_request(int fd)
{
    int request_id;
    int n = -1;

    /* 提取请求ID */
    n = recv(fd,&request_id,4,0);
    if(n == -1)
    {
        char errobuf[20];
        sprintf(errobuf,"recv fd[%d]",fd);
        perror(errobuf);
    }

    /* 客户连接断开 */
    if(n == 0)
    {
        printf("client %d close\n",fd);

        clients_mesg[fd].fd = -1;
        bzero(&clients_mesg[fd].username,16);

        close(fd);
        return;
    }
    printf("request_id:%d\n",request_id);


    /* 根据请求应答客户 */
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
