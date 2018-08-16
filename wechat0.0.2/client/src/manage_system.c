
#include "../include/head.h"
#include "../include/wechat.h"

void manage_system(int fd)
{
    //printf("\033[;31m*************暂不提供该功能*************** \033[0m");

    int select;
    char ch;
    do
    {
        ManageMenu();
        scanf("%d",&select);
        while((ch = getchar()) != '\n' && ch != EOF);

        switch(select)
        {
            case 1:     /* 好友管理 */
                friend_manage(fd);
                break;
            case 2:     /* 群管理 */
                printf("\033[;31m**********\
***暂不提供该功能*************** \033[0m");
                manage_system(fd);
                break;
            case 3:     /* 返回上一层 */
                main_page(fd);
                break;
            case 4:     /* 退出 */
                exit(0);
                break;
            default:
                printf("\n******************选择错误,请重新选择**************\n");
                break;
        }
    }while(select > 4 || select < 1);


    return ;
}
