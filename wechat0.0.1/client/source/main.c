
#include "../include/head.h"
#include "../include/wechat.h"
int main()
{
    //int sockfd = Socket(TCPCLIENT);
    //sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ServPort);
    inet_pton(AF_INET,ServIp,&serv_addr.sin_addr);

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
                exit(0);
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
