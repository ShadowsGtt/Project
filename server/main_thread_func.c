#include "gt.h"

/* 处理客户连接 */
void main_thread_func(int epollfd,struct epoll_event *ready_fd,threadpool_t *pool,int listenfd) 
{

    int *fd = malloc(8);
    fd[0] = listenfd;
    fd[1] = epollfd;
    while(1)
    {
        int rtnum = epoll_wait(epollfd,ready_fd,MAX_CONN,-1);
        for(int i = 0;i < rtnum;i++)
        {
            /* 有客户连接 */
            if(ready_fd[i].data.fd == listenfd && (ready_fd[i].events & EPOLLIN))
            {
                threadpool_add(pool,handle_connection,(void *)fd,0);

            }
            /* 有客户端发送请求 */
            else if( (ready_fd[i].data.fd != listenfd) &&  (ready_fd[i].events & EPOLLIN) )
            {
                int fd = ready_fd[i].data.fd;
                while(1)
                {
                    char buf[100];
                    int n = recv(fd,buf,sizeof(buf),0);
                    if(n < 0)
                    {
                        if( (errno == EWOULDBLOCK) || (errno == EAGAIN) )
                        {
                            fprintf(stderr,"no data\n");
                            break;
                        }
                        perror("recv");
                        close(fd);
                        break;
                    }
                    else if(n == 0)
                    {
                        printf("client close\n");
                        close(fd);
                    }

                    if(send(fd,buf,100,0) == -1 )
                    {
                        perror("send");
                    }

                }
                
            }

        }
        
        
        
        /*
        for(int t = 0;t < rtnum ; t++)
        {

            if( (Epoll_Cli[t].data.fd == sockfd) && (Epoll_Cli[t].events & EPOLLIN) )
            {
                sin_size = sizeof(their_addr);
                if(  (conn = (accept(sockfd,(struct sockaddr *)&their_addr,&sin_size)  )) == -1)
                {
                    perror("accept");
                    continue;
                }
                for(int k = 0; k < MaxClients;k++)
                {
                    if(clients[k].fd == -1)
                    {
                        Epoll_Cli[k].data.fd = conn;
                        clients[k].fd = conn;
                        // printf("accept fd:%d\n",clients[k].fd);
                        break;
                    }
                }
                printf("新客户已经链接！IP:%s,Port:%d\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port));
                printf("当前在线人数:%d\n",++total);
                //printf("newconnfd:%d\n",conn);
                rgfd.data.fd = conn;
                rgfd.events = EPOLLIN ;
                if(epoll_ctl(epollfd,EPOLL_CTL_ADD,conn,&rgfd) == -1) //将新连接的fd注册到epoll中
                {
                    perror("epoll_ctl");
                }
            }
            else if(Epoll_Cli[t].events & EPOLLIN) 
            {
                conn = Epoll_Cli[t].data.fd;
                if(conn == -1)
                    continue;
                numbytes = recv(conn,buf,sizeof(buf),0);
                Devide_Msg(buf,dname,newbuf,name);
                for(int i = 0;i < MaxClients;i++)
                {
                    if(clients[i].fd == conn)
                    {
                        strcpy(clients[i].name,name);
                        break;
                    }
                }
                if(numbytes == -1)
                {
                    perror("recieve");
                    exit(0);
                }
                else if(numbytes == 0)
                {
                    printf("Port = %d已经关闭连接!\n",ntohs(their_addr.sin_port));
                    printf("当前在线人数:%d\n",--total);
                    clients[t].fd = -1;
                    Epoll_Cli[t].data.fd = -1;
                    close(conn);
                    memset(clients[t].name,0,sizeof(clients[t].name));
                }
                else
                {
                    printf("name=%s\n",name);
                    printf("dname=%s\n",dname);
                    printf("msg=%s\n",newbuf);
                    sendfd = Get_sendfd(msg,name,newbuf,dname);
                    if(sendfd != -1)
                    {
                        strcat(sendmsg,name);
                        strcat(sendmsg,":");
                        strcat(sendmsg,newbuf);
                        msg[strlen(sendmsg)] = '\0';
                        send(sendfd,sendmsg,sizeof(sendmsg),0);
                    }
                }
            }
        }
        memset(buf,0,sizeof(buf));
        memset(name,0,sizeof(name));
        memset(dname,0,sizeof(dname));
        memset(newbuf,0,sizeof(newbuf));
        memset(msg,0,sizeof(msg));
        memset(sendmsg,0,sizeof(sendmsg));
        */
    }
}
