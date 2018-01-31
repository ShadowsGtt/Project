#include "gt.h"

void handle_sign_in(int fd)
{
    struct 
    {
        int length;
        char sour[16];
        char dest[16];
        char password[16];
    }request;
    int n = recv(fd,&request,sizeof(request),0);
    printf("source:%s\ndest:%s\n",request.sour,request.dest);
    printf("password:%s\n",request.password);
}
