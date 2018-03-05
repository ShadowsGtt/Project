
#include "../include/head.h"
#include "../include/wechat.h"

void recv_fri_mesg(int fd)
{
    struct 
    {
        char src_name[16];
        char dst_name[16];
        char mesg[MAXMESGLEN];
    }mesg;
}
