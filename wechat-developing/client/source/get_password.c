
#include "../include/head.h"
#include "../include/wechat.h"

void get_password(char* const password)
{
    struct termios new_set,old_set;
    tcgetattr(STDIN_FILENO,&old_set); 
    new_set = old_set;                          /* 新设置和原设置除终端回写外其他保持一致 */

    new_set.c_lflag &= ~ECHO;                   /* 关闭回终端回显功能*/

    if( tcsetattr(STDIN_FILENO,TCSANOW,&new_set) != 0 )   /* 应用新终端设置 */
    {
        fprintf(stderr,"set failed");
    }
    fgets(password,16,stdin);                   /* 输入字符不会在终端显示 */

    password[strlen(password)-1] = 0;           /* 去除fget获取的末尾回车 */

    tcsetattr(STDIN_FILENO,TCSANOW,&old_set);   /* 恢复旧的终端设备 */
}

