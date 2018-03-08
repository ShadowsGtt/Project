
#include "../include/head.h"
#include "../include/wechat.h"

void friend_talk(int fd)
{
    fd = sockfd; 
    //printf("\033[;31m*************暂不提供该功能*************** \033[0m");
    int file_fd;
    char file_name[26];// = "FRIENDTABLE.txt";
    char friend[10][16] = {0};

    sprintf(file_name,"%sFRITAB.txt",username);
    struct 
    {
        int type;
        char dst_name[16];
        char src_name[16];
        char mesg[MAXMESGLEN];
    }mesg = {CHAT,{0},{0},{0}};
    strcat(mesg.src_name,username);

    file_fd = open(file_name,O_RDONLY,S_IRUSR);
    if(file_fd == -1)
        perror("open");
    
    int n = read(file_fd,friend,32768);
    if(n == -1)
        perror("read in friend_talk");

    if(friend[0][0] == 0)
    {
        printf("\n------------您的帐号暂无好友---------------\n");
        
    }
    else
    {
        printf("\n---------------选择一位好友-------------------\n");
        int k = 0;
        while(friend[k][0] != 0)
        {
            printf("---------------------\n");
            printf("     %d.%s\n",k+1,friend[k]);
            k++;
        }
        printf("---------------------\n");
        printf("请选择:");
        int select = -1;
        scanf("%d",&select);
        char ch;
        while((ch = getchar()) != '\n' && ch != EOF);
        while(select > k || select < 1)
        {
            printf("选择错误,请重新选择:");
            scanf("%d",&select);
            while((ch = getchar()) != '\n' && ch != EOF);
        }

        strncat(mesg.dst_name,friend[select-1],16);

        printf("dst_name:%s\n",mesg.dst_name);

        system("clear");
        printf("\033[;34m\t\t\t[使用<ctrl> + <D>退出]\t\t\t\033[0m\n");
        printf("-------------------------------------------------\n");
        printf("\033[;34m\t\t\t正在与[%s]聊天中\t\t\t\033[0m\n",mesg.dst_name);
        printf("-------------------------------------------------\n");


        //printf(BLUE_S"使用<ctrl> + <D> 退出聊天\n"BLUE_E);
        printf("->");
        while(fgets(mesg.mesg,sizeof(mesg.mesg),stdin) != NULL)
        {
            printf("->");
            fflush(stdout);
            int n = send(sockfd,&mesg,sizeof(mesg),0);
            if(n == -1)
                perror("send in friend_talk");
            bzero(&mesg.mesg,sizeof(mesg.mesg)); 
        }
        printf("\n-------------------------------------------------\n");
        printf("\033[;34m\t\t\t您已退出与[%s]聊天\t\t\t\033[0m\n",mesg.dst_name);
        printf("-------------------------------------------------\n");
    }

    main_page(sockfd);

    return ;
}
