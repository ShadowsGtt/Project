#include "../include/wechat.h"
int main()
{
    int sockfd = Socket(TCPCLIENT);

    int select;
    char ch;
    do
    {
        LoginMenu();
        scanf("%d",&select);
        while((ch = getchar()) != '\n' && ch != EOF);
        switch(select)
        {
            case 1:     /* 登录 */
                sign_in(sockfd);
                break;
            case 2:     /* 注册 */
                sign_up(sockfd); 
                break;
            case 3:     /* 退出 */
                break;
            default:
                printf("\n******************选择错误,请重新选择**************\n");
                break;
        }
    }while(select > 3 || select < 1 || select == 2);
    
    /* 登录以后*/
    main_page(sockfd); 
    
    return 0;
}
