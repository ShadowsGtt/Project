#include<iostream>
#include "../include/ReadConfig.h"
#include "../include/Server.h"
using namespace std;

int main()
{
    Server *server = Server::newServer();
    server->Run(); 

    return 0;
}
