#include "../include/wechat.h"

void manage_system(int fd)
{
    printf("\033[;31m*************暂不提供该功能*************** \033[0m");
    fflush(stdout);
    sleep(1);
    main_page(fd);
    return ;
}
