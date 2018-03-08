#include "../include/head.h"
#include "../include/wechat.h"

int sign_in(int fd)
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct 
    {
        int request;
        char UID[16];
        char Passwd[16];
    }message;

    struct 
    {
        int res;
        char message[100];
    }reply= {-1,{0}};

    message.request = SIGNIN;


    char ch;
    printf("\n请输出您的用户名:");
    scanf("%s",message.UID);
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("请输入密码:");
    
    get_password(message.Passwd);

    putchar(10);
    //open_noblock(sockfd);
    
    while(1)
    {
        int rrr = -1;
        if(rrr = connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)  ) == -1 )
        {
            if(errno == ECONNREFUSED)
            {
                fprintf(stderr,"连接失败,正在重新连接...\n");
                sleep(1);
                close(sockfd);
                sockfd = socket(AF_INET,SOCK_STREAM,0);
                continue;
            }
            else if(errno == ECONNRESET)
            {
                fprintf(stderr,"与服务器断开连接!\n正在重新连接...\n");
                close(sockfd);
                sockfd = socket(AF_INET,SOCK_STREAM,0);
                continue;

            }
            else if(errno == EINPROGRESS )
            {
                fprintf(stderr,"正在与连接服务器....\n");
                break;
                
            }
            else if(errno == ENETUNREACH )
            {
                fprintf(stderr,"服务器不可达,请检查您的网络连接!\n");
                close(fd);
                sockfd = socket(AF_INET,SOCK_STREAM,0);
                continue;    
            }
        }
        else
            break;
    }
    printf("\n正在登录中...\n");

    int n = send(sockfd,&message,sizeof(message),0 );

    if(n == -1)
    {
        perror("error:");
    }
    else
    {
        /* 输出服务器回馈消息  */
        n = recv(sockfd,&reply,sizeof(reply),0);
        
        if(n == -1)
            fprintf(stderr,"server closed\n");
        
        fprintf(stdout,"\n\033[;31m***********%s***************\033[0m\n",reply.message);
        /* 登录失败 */
        if(reply.res == -1)  
        {
            close(sockfd);
            sign_in(fd);
        }
        /* 登录成功 */
        if(reply.res == 0)
        {
            strcat(username,message.UID);

            /* 启动接受消息的线程 */
            if(pthread_create(&tid,NULL,thread_read,(void *)&sockfd) != 0 )
                perror("thread create");

            /* 发送获取好友表请求 */

            int type = GETFRITAB;
            n = send(sockfd,&type,sizeof(type),0);
            if(n == -1)
                perror("send get friend table");
            fflush(stdout);
            //main_page(sockfd);

            
            
        }
    }
        return reply.res;
}
