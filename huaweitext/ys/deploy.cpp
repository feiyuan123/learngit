#include "deploy.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX_LINE_LEN 55000

#define INLINE  static __inline
#ifdef _DEBUG
#define PRINT   printf
#else
#define PRINT(...)
#endif

int N,M,K,ServiceCost,text;

struct Edge  
{  
    int from, to, cap, flow, next;  
};  
Edge edge[MAXN]; 
int head[MAXN], edgenum, cur[MAXN],goal[MAXN][MAXN];  
int cost[MAXN][MAXN];
int dist[MAXN];  
bool vis[MAXN]; 

void init()  
{  
    edgenum = 0;  
    memset(head, -1, sizeof(head));
    memset(cost,0,sizeof(cost)); 
    memset(goal,0,sizeof(goal)); 
}  

void addEdge(int u, int v, int w ,int f)  
{  
    Edge E1 = {u, v, w, 0, head[u]};  
    edge[edgenum] = E1;  
    head[u] = edgenum++;  
    Edge E2 = {v, u, w, 0, head[v]};  
    edge[edgenum] = E2;  
    head[v] = edgenum++;
    cost[u][v]=cost[v][u]=f;
}  

void read_file1(char ** const buff, const unsigned int spec, const char * const filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
    	PRINT("Fail to open file %s, %s.\n", filename, strerror(errno));
    }
    PRINT("Open file %s OK.\n", filename);

    char line[MAX_LINE_LEN + 2];
    unsigned int cnt = 0;
    while ((cnt < spec) && !feof(fp))
    {
        line[0] = 0;
        if (fgets(line, MAX_LINE_LEN + 2, fp) == NULL)  continue;
        if (line[0] == 0)   continue;
        buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
        strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
        buff[cnt][MAX_LINE_LEN + 1] = 0;
        cnt++;
    }
	int x,y,w,f,flag = 0;
	N = atoi(strtok(buff[0]," "));
	M = atoi(strtok(NULL," "));
	K = atoi(strtok(NULL," "));
	ServiceCost =  atoi(strtok(buff[2]," "));
	x = atoi(strtok(buff[100]," "));
	//y = atoi(strtok(NULL," "));
	//w = atoi(strtok(NULL," "));
	//goal[x][y]=w;
	/*
	for( unsigned int i = 4 ; i < 102; i++)
	{

		
		if(!flag)
		{
			x = atoi(strtok(buff[i]," "));
			y = atoi(strtok(NULL," "));
			w = atoi(strtok(NULL," "));
			f = atoi(strtok(NULL," "));
			addEdge(x,y,w,f);
		}
		
		else if	(atoi(strtok(buff[i]," "))==0&&atoi(strtok(NULL," "))==0)
			flag = 1;

		else if( i==101)
		{
			x = atoi(strtok(buff[i]," "));
			y = atoi(strtok(NULL," "));
			w = atoi(strtok(NULL," "));
			goal[x][y]=w;
		}
		
		
	}
	*/
    fclose(fp);
}

//You need to complete the function 
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
	init(); 
	read_file1(topo, MAX_EDGE_NUM, filename);
	printf("%d %d %d %d\n",N,M,K,ServiceCost);
	printf("%d %d %d %d\n",edge[0].from,edge[0].to,edge[0].cap,cost[edge[0].from][edge[0].to]);
	//printf("0 43 %d\n",goal[0][43]);
/*
	// Output demo
	char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

	write_result(topo_file, filename);
*/

}
