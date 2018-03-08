
#include "../include/wechat.h"
#include "../include/database.h"

/* 好友添加结果 */
void handle_radd_fri(int fd)
{
    int n = -1;
    char sql[200] = {0};

    /* 用户请求 */
    struct 
    {
        int type;
        char dst_name[16];
        char src_name[16];
        char res;
    }mesg;
    bzero(&mesg,sizeof(mesg));

    /* 反馈用户请求 */
    struct 
    {
        int type;
        char mesg[MAXMESGLEN];
    }reply={RADDFRI,{0}};


    n = recv(fd,&mesg,sizeof(mesg),0 );
    if(n == -1)
        perror("in reply add friend");

    /* 同意添加好友 */
    if(mesg.res == 'y')
    {
        /* 记录数据库 */
        bzero(sql,sizeof(sql) );
        sprintf(sql,"insert into Friend(UID,FID) values('%s','%s') ",\
                mesg.dst_name,mesg.src_name);

        /* 通知主动添加者 */
        int dst_fd = -1;
        dst_fd = get_fd_byname(mesg.dst_name);
        if(dst_fd != -1) 
        {
            sprintf(reply.mesg,"[%s]同意了你的好友添加请求!",mesg.src_name); 
            n = send(dst_fd,&reply,sizeof(reply),0 );
            if(n == -1)
                perror("in handle_add_fri [send1]");
        }
        
        
    }
    /* 拒绝添加好友 */
    else if(mesg.res == 'n')
    {
        int dst_fd = -1;
        dst_fd = get_fd_byname(mesg.dst_name);
        if(dst_fd != -1) 
        {
            sprintf(reply.mesg,"[%s]拒绝了你的好友添加请求!",mesg.src_name); 
            n = send(dst_fd,&reply,sizeof(reply),0 );
            if(n == -1)
                perror("in handle_add_fri [send1]");
        }

    }



}

void handle_add_fri(int fd)
{

    printf("-----------in handle_add_fri----------------\n");

    int n = -1;
    char sql[200] = {0};


    /* 用户请求 */
    struct 
    {
        int type;
        char dst_name[16];
        char src_name[16];
    }mesg;
    bzero(&mesg,sizeof(mesg));

    /* 反馈用户请求 */
    struct 
    {
        int type;
        char mesg[MAXMESGLEN];
    }reply={RADDFRI,{0}};

    n = recv(fd,&mesg,sizeof(mesg),0);
    if(n == -1)
        perror("recv,get GETFRITAB");

    sprintf(sql,"select UID from UserTable where UID='%s'",mesg.dst_name);
    n = select_result(CONN_MYSQL,sql);
    /* 存在目标用户 */
    if(n == 0)
    {
        /* 通知目标者 */
        int dst_fd = -1;
        dst_fd = get_fd_byname(mesg.dst_name);
        if(dst_fd != -1) 
        {
            /* 目标者在线立刻通知目标者 */
            n = send(dst_fd,&mesg,sizeof(mesg),0 );
            if(n == -1)
                perror("in handle_add_fri [send1]");
        }
        else
        {
            /* 目标者不在线,告知请求者暂不支持离线添加,后期再做消息后台化 */
            sprintf(reply.mesg,"好友[%s]未在线,暂不支持离线添加好友!",mesg.dst_name); 
            n = send(fd,&reply,sizeof(reply),0 );
            if(n == -1)
                close(fd);
        }
    }
    /* 不存在目标用户 */
    else if(n == -1)
    {
        /* 通知请求者 */
        sprintf(reply.mesg,"添加失败!不存在用户[%s]",mesg.dst_name);

        n = send(fd,&reply,sizeof(reply),0 );
        if(n == -1)
            close(fd);
    }














#if 0
    /* 存在目标用户 */
    if(n == 0)
    {
        /* 修改数据库 */
        char sql[200] ;
        bzero(sql,sizeof(sql));

        sprintf(sql,\
"select * from Friend where (UID='%s' and FID='%s') or (UID='%s' and FID='%s') ",\
mesg.dst_name,mesg.src_name,mesg.src_name,mesg.dst_name  );
        
        if(!select_result(CONN_MYSQL,sql) )
        {//从未添加过好友
            bzero(sql,sizeof(sql));
            sprintf(sql,"insert into Friend(UID,FID,UserToFri,FriToUser) \
                    values('%s','%s','%s','%s') ",\
                    mesg.src_name,mesg.dst_name,"Y","N" );
        }
        else
        {
            bzero(sql,sizeof(sql));
            sprintf(sql,"select * from Friend \
                    where ( (UID='%s' and FID='%s') and\
                    (UserToFri='Y' and FriToUser='N') ) or( (UID='%s' and FID='%s') \
                        and (UserToFri='N' and FriToUser='Y')  ) ",\
                    mesg.src_name,mesg.dst_name,mesg.dst_name,mesg.src_name);

            /* 如果请求者之前添加过目标者,但目标未添加请求者 */
            if(select_result(CONN_MYSQL,sql) == 0)
            {
                /* 通知目标者 */
                int dst_fd = -1;
                dst_fd = get_fd_byname(mesg.dst_name);
                if(dst_fd != -1) 
                {
                    /* 目标者在线立刻通知目标者 */
                    n = send(dst_fd,&mesg,sizeof(mesg),0 );
                    if(n == -1)
                        perror("in handle_add_fri [send1]");
                }
                else
                {
                    /* 目标者不在线,则消息后台化 */
                    
                }
            }

            bzero(sql,sizeof(sql));
            sprintf(sql,"select UID from Friend \
                    where (UID='%s' and FID='%s') and\
                    (UserToFri='Y' and FriToUser='N')",mesg.src_name,mesg.dst_name);

            /*如果目标者添加过请求者,但是请求者未添加目标者*/
            if()
            {
                
            }
            /* 通知请求者消息已发出 */
            sprintf(reply.mesg,"添加[%s],消息已发出!",mesg.dst_name);

            n = send(fd,&reply,sizeof(reply),0 );
            if(n == -1)
                close(fd);
            

            //sprintf(sql,"update Friend set UserToFri='Y' where UID='%s' and\
            FID='%s'",mesg.src_name,mesg.dst_name);
            //sprintf(sql,"update Friend set UserToFri='N' where UID='%s' and FID='%s'",mesg.dst_name,mesg.src_name);
        }

    
    }
    /* 不存在目标用户 */
    else if(n == -1)
    {
        /* 通知请求者 */
        sprintf(reply.mesg,"添加失败!不存在用户[%s]",mesg.dst_name);

        n = send(fd,&reply,sizeof(reply),0 );
        if(n == -1)
            close(fd);
    }
    
    //char user[16] = {0};
    //strncat(user,clients_mesg[fd].username,16);
    printf("[%s] <- add -> [%s]\n",mesg.src_name,mesg.dst_name);
    
    
    
    //mysql_free_result(result); // 释放结果集
    
#endif
    /* 将fd事件回写成可读 */
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }
}
