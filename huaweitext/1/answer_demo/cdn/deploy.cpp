#include "deploy.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <iostream>

using namespace std;
int N,M,K,ServiceCost,text;//N表示起始ID，M表示终止ID，K表示总带宽大小，ServiceCost表示单位网络租赁费

void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
     N = 0,M=0,K=0;
    char *c;
    int spaceCount = 0;
    c = topo[0];
    
    while (*c != '\0' && *c != '\n' && *c != '\r') 
    {
	while(*c!=' ')
	{
	   N = *c - '0' + N * 10;
	   c++;
	}	
        if (*c == ' ') 
        {
            c++;
            spaceCount++;
            continue;
        }
        if (spaceCount == 1)
        {
           M = *c - '0' + M * 10;
        }
        if (spaceCount == 2) 
        {
            K = *c - '0' + K * 10;
        }
        c++;
    }
    
    string res;
    char a[20];
    sprintf(a, "%d %d %d\n\n",N,M,K);
    res = a;
    int netnode, need;
    /*
    for (int i = 1; i < consumerNum+1; i++)
    {
        c = topo[line_num-i];
        netnode = need = spaceCount = 0;
        while (*c != '\0' && *c != '\n' && *c != '\r') 
        {
            if (*c == ' ') 
            {
                c++;
                spaceCount++;
                continue;
            }
            if (spaceCount == 1)
            {
                netnode = *c - '0' + netnode * 10;
            }
            else if (spaceCount == 2) 
            {
                need = *c - '0' + need * 10;
            }
            c++;
        }
        sprintf(a, "%d %d %d",netnode,consumerNum-i,need);
        res += a;
        if (i != consumerNum) 
        {
            res += "\n";
        }
    }
    */
    char * topo_file = (char *)res.c_str();
    write_result(topo_file, filename);
}
