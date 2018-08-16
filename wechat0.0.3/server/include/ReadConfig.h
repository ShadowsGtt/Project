#ifndef _READCONFIG_H
#define _READCONFIG_H

#include <string>
#include <map>
using namespace std;
 
#define COMMENT_CHAR '#'
 
extern bool ReadConfig(const string & filename, map<string, string> & m);
extern void PrintConfig(const map<string, string> & m);
#endif
