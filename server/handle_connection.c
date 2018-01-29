#include "gt.h"

void handle_connection(void *fd)
{

    int client_len = sizeof(struct sockaddr_in);
    int new_fd ;
    int listenfd = ((int *)fd)[0];
    int epollfd = ((int *)fd)[1];
    
    if((new_fd = accept(listenfd,(struct sockaddr *)&client_addr,&client_len)) == -1)
    {
        if(new_fd == -1)
        {
            perror("accept");
        }
    }
    open_noblock(new_fd);
    //printf("%d newclient->ip:%s\tport:%d\n",++num,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    register_epoll_fd(epollfd,new_fd,1);


}
