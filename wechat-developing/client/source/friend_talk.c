
#include "../include/head.h"
#include "../include/wechat.h"

void friend_talk(int fd)
{
    
    //printf("\033[;31m*************暂不提供该功能*************** \033[0m");
    //fflush(stdout);
    //sleep(1);
    //main_page(fd);

    struct 
    {
        int type;
        int length;
        char src_name[16];
        char dst_name[16];
        char msg[MAXMESGLEN];
    }mesg = {CHAT,0,{0},{0},{0}};
    strcat(mesg.src_name,username);
    printf("---------------选择一位好友-------------------");
    return ;
}
