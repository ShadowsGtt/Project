
#include "../include/head.h"
#include "../include/wechat.h"

void add_friend(int );

/* 请求添加好友 */
void add_friend(int fd)
{
    char ch;
    int n = -1;

    struct 
    {
        int type;
        char dst_name[16];
        char src_name[16];
    }mesg={ADDFRI,{0},{0}};
    strncat(mesg.src_name,username,16);
    
    printf("请输入对方的用户名:");
    scanf("%s",mesg.dst_name);
    while((ch = getchar()) != '\n' && ch != EOF);

    n = send(fd,&mesg,sizeof(mesg),0);
    if(n == -1)
        perror("in add_friend [send]");
    friend_manage(fd);
}

/* 好友添加结果 */
void res_add_friend(int fd)
{   
    char res[MAXMESGLEN] = {0};

    int n = -1;

    n = recv(fd,res,32767,0);
    if(n == -1)
        perror("in res_add_friend [recv]");
    
    printf("\n---------------新消息-----------------\n");
    printf("%s\n",res);
    printf("---------------------------------------\n");
    fflush(stdout);
}

/* 收到添加好友请求 */
void recv_add_fri(int fd)
{
    //printf("------------in recv_add_fri-----------\n");
    int n = -1;

    struct 
    {
        char dst_name[16];
        char src_name[16];
    }mesg;
    n = recv(fd,&mesg,sizeof(mesg),0);
    if(n == -1)
        perror("in recv_add_friend [recv]");
    printf("\n---------------新消息-----------------");
    printf("\n[%s]添加您为好友(y/n)\n",mesg.src_name);

    char sel,ch;

    while((sel = getchar()) != 'y' && sel != 'n')
    {
        printf("请输入正确的选择!\n");
        while((ch = getchar()) != '\n' && ch != EOF);
        sel = getchar();
        while((ch = getchar()) != '\n' && ch != EOF);

    }
    if(sel == 'y')
    {
        struct 
        {
            int type;
            char dst_name[16];
            char src_name[16];
            char res;
        }mesgs={RADDFRI,{0},{0},'y'};
        strncat(mesgs.src_name,username,16);
        strncat(mesgs.dst_name,mesg.src_name,16);

        int n = send(fd,&mesgs,sizeof(mesgs),0);
        if(n == -1)
            perror("send in recv_add_fri,add");
    }
    if(sel == 'n')
    {
        struct 
        {
            int type;
            char dst_name[16];
            char src_name[16];
            char res;
        }mesgs={RADDFRI,{0},{0},'n'};
        strncat(mesgs.src_name,username,16);
        strncat(mesgs.dst_name,mesg.src_name,16);

        int n = send(fd,&mesgs,sizeof(mesgs),0);
        if(n == -1)
            perror("send in recv_add_fri,add");
        
    }
    printf("---------------------------------------\n");
}

void friend_manage(int fd)
{
    //printf("-----------------in friend_manage-----------------\n");
    int select;
    char ch;
    do
    {
        FriendManageMenu();
        scanf("%d",&select);
        while((ch = getchar()) != '\n' && ch != EOF);

        switch(select)
        {
            case 1:     /* 添加好友 */
                add_friend(fd);
                break;
            case 2:     /* 删除好友 */
                printf("\033[;31m**********\
***暂不提供该功能*************** \033[0m");
                friend_manage(fd);
                break;
            case 3:     /* 查看我的好友 */
                printf("\033[;31m**********\
***暂不提供该功能*************** \033[0m");
                friend_manage(fd);
                break;
            case 4:     /* 修改好友备注 */
                printf("\033[;31m**********\
***暂不提供该功能*************** \033[0m");
                friend_manage(fd);
                break;
            case 5:     /* 返回上一层 */
                manage_system(fd);
                break;
            case 6:     /* 退出 */
                exit(0);
                break;
            default:
                printf("\n******************选择错误,请重新选择**************\n");
                break;
        }
    }while(select > 6 || select < 1);


    return ;
}
