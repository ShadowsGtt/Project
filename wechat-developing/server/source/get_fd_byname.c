#include "../include/wechat.h"
#include "../include/threadpool.h"
#include "../include/database.h"

int get_fd_byname(const char *name)
{
    int fd = -1;
    for(int i = 0 ; i < MAX_CONN;i++)
    {
        if(clients_msg[i].fd == -1)
            break;
        if(strcmp(clients_msg[i].username,name) == 0)
            fd = clients_msg[i].fd;
    }
    return fd;
}
