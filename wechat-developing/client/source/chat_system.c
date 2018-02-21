#include "../include/head.h"
#include "../include/wechat.h"

void chat_system(int fd)
{
    int select;
    char ch;
    do
    {
        ChatMenu();
        scanf("%d",&select);
        while((ch = getchar()) != '\n' && ch != EOF);

        switch(select)
        {
            case 1:     /* 群聊天 */
                group_talk(fd);
                break;
            case 2:     /* 好友聊天 */
                friend_talk(fd);
                break;
            case 3:     /* 返回上一层 */
                main_page(fd);
                break;
            case 4:     /* 退出 */
                exit(0);
            default:
                printf("\n******************选择错误,请重新选择**************\n");
                break;
        }
    }while(select > 4 || select < 1);
}
