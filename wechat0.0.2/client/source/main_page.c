
#include "../include/head.h"
#include "../include/wechat.h"

void main_page(int fd)
{
    
    int select;
    char ch;
    do
    {
        MainMenu();
        scanf("%d",&select);
        while((ch = getchar()) != '\n' && ch != EOF);

        switch(select)
        {
            case 1:     /* 聊天系统 */
                chat_system(fd);
                break;
            case 2:     /* 管理系统 */
                manage_system(fd);
                break;
            case 3:     /* 退出 */
                exit(0);
                break;
            default:
                printf("\n******************选择错误,请重新选择**************\n");
                break;
        }
    }while(select > 3 || select < 1);
}
