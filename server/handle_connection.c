#include "../include/gt.h"

void handle_connection(int listenfd)
{

    struct sockaddr_in client_addr;
    int client_len = sizeof(struct sockaddr_in);
    int new_fd ;
   
    if((new_fd = accept(listenfd,(struct sockaddr *)&client_addr,&client_len)) == -1)
    {
        if(new_fd == -1)
        {
            perror("accept");
        }
    }
    //open_noblock(new_fd);
    printf("%d newclient->ip:%s\tport:%d\n",++num,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    register_epoll_fd(epollfd,new_fd,0);
    clients_msg[new_fd].fd = new_fd;


}
