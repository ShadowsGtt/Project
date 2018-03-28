#include "../include/wechat.h"
#include "../include/database.h"

void handle_get_fritab(int fd)
{

    printf("-----------in handle_get_fritab----------------\n");

    int i = 0;
    int n = -1;
    MYSQL_RES *result; // mysql 记录集
    MYSQL_ROW row;
    char sql[200] = {0};


    /* 用户请求得到的信息 */
    struct 
    {
        int type;
        char friend[10][16];
    }reply;

    bzero(&reply,sizeof(reply));

    n = recv(fd,&reply,4,0);
    if(n == -1)
        perror("recv,get GETFRITAB");


    //sprintf(sql,"select UID,FID from Friend where\
            (UID='%s' or FID='%s') and \
            (FriToUser='Y' and UserToFri='Y') ",\
            clients_mesg[fd].username,clients_mesg[fd].username);
    
    sprintf(sql,"select UID,FID from Friend where\
            (UID='%s' or FID='%s') ",\
            clients_mesg[fd].username,clients_mesg[fd].username);

    int res = mysql_query(CONN_MYSQL,sql);
    if (!res) 
    {
        //printf("Inserted %lu rows\n", (unsigned long)mysql_affected_rows(conn));
    } else 
    {
        fprintf(stderr, "error %d: %s\n", mysql_errno(CONN_MYSQL), mysql_error(CONN_MYSQL));
        return ;
    }
    
    
    result = mysql_store_result(CONN_MYSQL);
    
    printf("[%s] friends\n",clients_mesg[fd].username);
    while ((row=mysql_fetch_row(result))) // 打印结果集
    {
        printf("row0:%s\trow1:%s\n",row[0],row[1]);
        if(strcmp(row[0],clients_mesg[fd].username) != 0 )
        {
            strncat(reply.friend[i],row[0],16);
        }
        if(strcmp(row[1],clients_mesg[fd].username) != 0 )
        {
            strncat(reply.friend[i],row[1],16);
        }
        
        printf("friend[%d]:%s\n",i,reply.friend[i]);
        i++;
    }
    
    n = send(fd,&reply,sizeof(reply),0 );
    if(n == -1)
        perror("in get friend,send");

    mysql_free_result(result); // 释放结果集
    
    /* 将fd事件回写成可读 */
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }
}
