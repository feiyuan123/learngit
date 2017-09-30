#include "deploy.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
#include <stack>
#include <set>
#include <math.h>
#include <string.h>
#include <time.h>

using namespace std;
#define INF 0x3f3f3f3f
#define min(a,b) (a>b?b:a)
#define CLR(a, b) memset(a, (b), sizeof(a))
#define MAXN 5000

int N,M,K,ServiceCost;
int source, sink,sumgoal,number,num;

struct Edge
{
    int from, to, cap, flow,cost, next;
};
Edge edge[550000];
int head[MAXN], edgenum, cur[MAXN];
int cost[MAXN][MAXN],pre[MAXN];
int dist[MAXN];
bool vis[MAXN];
stack<int> path[MAXN];

//#define N     30      
#define T     3500    
#define EPS   1e-8   
#define DELTA 0.95    
#define LIMIT 130  
#define OLOOP 500   
#define ILOOP 500  
set<int>answer;
set<int>curPath,newPath;
clock_t start;
clock_t finish;
void init()
{
    edgenum = 0;
    sumgoal = 0;
    memset(head, -1, sizeof(head));
    memset(cost, 0 , sizeof(cost));
    source = 1000, sink = 1001;
}

void addEdge(int u, int v, int w , int c)
{
    Edge E1 = {u, v, w, 0, c, head[u]};
    edge[edgenum] = E1;
    head[u] = edgenum++;
    Edge E2 = {v, u, 0, 0, c, head[v]};
    edge[edgenum] = E2;
    head[v] = edgenum++;
   // cost[u][v]=cost[v][u]=f;
}
void addEdge1(int u, int v, int w , int c)
{
    Edge E1 = {u, v, w, 0, c, head[u]};
    edge[edgenum] = E1;
    head[u] = edgenum++;
    Edge E2 = {v, u, 0, 0, -c, head[v]};
    edge[edgenum] = E2;
    head[v] = edgenum++;
   // cost[u][v]=cost[v][u]=f;
}

bool SPFA(int s, int t)
{
    queue<int> Q; CLR(dist, INF); CLR(vis, false); CLR(pre, -1);
    vis[s] = true; dist[s] = 0; Q.push(s);
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            Edge E = edge[i];
            if(dist[E.to] > dist[u] + E.cost && E.cap > E.flow)
            {
                dist[E.to] = dist[u] + E.cost;
                pre[E.to] = i;
                if(!vis[E.to])
                {
                    vis[E.to] = true;
                    Q.push(E.to);
                }
            }
        }
    }
    return pre[t] != -1;
}

void MCMF(int s, int t, int &flow, int &cost)
 {
    int i;
    num = 0;
    flow = cost = 0;
    while(SPFA(s, t))
    {
        while(!path[num].empty()) path[num].pop();
        int Min = INF;
        for( i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            Edge E = edge[i];
            Min = min(Min, E.cap - E.flow);
        }
        path[num].push(Min);
        for(i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            path[num].push(edge[i].from);
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            //cout << edge[i].cost << endl;
            cost += edge[i].cost * Min;
        }
        flow += Min;

        num++;
    }
}



set<int> GetNext(set<int> p)
{
    int i;
    set<int> ans = p;
    int k = ans.size();
    set<int>::iterator it;
    int z = (int)(2 * (rand() / (RAND_MAX + 1.0)));
    int x = (int)(k * (rand() / (RAND_MAX + 1.0)));
    for( i = 0 ; i < x ; i++)
    {
        it = ans.begin();
        int y = (int)(k * (rand() / (RAND_MAX + 1.0)));
        int g = (int)((N-1) * (rand() / (RAND_MAX + 1.0)));

        if(z==0)
        {
            while(y--)
            {
                it++;
            }
            ans.erase(it);
            k--;
        }
        if(z==1)
        {
            if(ans.find(g)==ans.end())
            {
                ans.insert(g);
            }
        }
    }
    return ans;
}

int calc(set<int> a)
{
    int i,number = 0;
    set<int>::iterator it;
    for( it = a.begin() ; it!=a.end(); it++)
    {
        addEdge(source,*it,INF,0);
        number++;
    }
    int flow, cost;
    MCMF(source, sink, flow, cost);
    for( i = 0 ; i <= edgenum ; i++)
    {
        edge[i].flow = 0;
    }
    for(i = head[source]; i != -1; i = edge[i].next)
    {
        edge[i].cap = 0;
    }
    if(flow == sumgoal)
        return number*ServiceCost+cost;
    else
        return -1;
}

void SA()
{
    int i;
    double t = T;
    srand(time(NULL));

    curPath = answer;
    newPath = answer;
    int P_L = 0;
    int P_F = 0;
    while(1)      
    {
        for(int i = 0; i < ILOOP; i++)    
        {
            newPath = GetNext(curPath);
            double len1 = calc(newPath);
             len1 = calc(newPath);
            if(len1!=-1)
            {
                double len2 = calc(curPath);
                double dE = len1 - len2;
                if(dE < 0)  
                {
                    curPath = newPath;
                    P_L = 0;
                    P_F = 0;
                }
                else
                {
                    double rd = rand() / (RAND_MAX + 1.0);
                    if(exp(dE / t) > rd && exp(dE / t) < 1)   
                        curPath = newPath;
                    P_L++;
                }
            }
            if(P_L > LIMIT)
            {
                P_F++;
                break;
            }
        }
        if(calc(curPath) < calc(newPath))
            answer = curPath;
        if(P_F > OLOOP || t < EPS)
            break;
        t *= DELTA;
	finish = clock();
    if(((finish - start) / CLOCKS_PER_SEC)>80)
		break;
    }

}

void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
	start = clock();
    init();
    N = 0,M=0,K=0,ServiceCost=0;
    char *c;
    int spaceCount = 0;
    
    c = topo[0];
    
    while (*c != '\0' && *c != '\n' && *c != '\r') 
    {
        if (*c == ' ') 
        {
            c++;
            spaceCount++;
            continue;
        }
        if (spaceCount == 0)
        {
           N = *c - '0' + N * 10;
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
    
    c = topo[2];
    spaceCount = 0;
    while (*c != '\0' && *c != '\n' && *c != '\r')
    {
        if (*c == ' ')
        {
            c++;
            spaceCount++;
            continue;
        }
        if (spaceCount == 0)
        {
           ServiceCost = *c - '0' + ServiceCost * 10;
        }
        c++;
    }
    int x,y,w,f;
    for( unsigned int i = 4 ; i < line_num ; i++)
    {
        c = topo[i];

        x = y = w = f = spaceCount = 0;
        if(i<line_num-K)
        {
            while (*c != '\0' && *c != '\n' && *c != '\r')
            {
                if (*c == ' ')
                {
                    c++;
                    spaceCount++;
                    continue;
                }
                if(spaceCount == 0)
                {
                   x = *c - '0' + x * 10;
                }
                if(spaceCount == 1)
                {
                  y = *c - '0' + y * 10;
                }
                if(spaceCount == 2)
                {
                   w = *c - '0' + w * 10;
                }
                if (spaceCount == 3)
                {
                   f = *c - '0' + f * 10;
                }
                c++;
            }
            addEdge1(x,y,w,f);
            addEdge1(y,x,w,f);
        }
        else
        {
            while (*c != '\0' && *c != '\n' && *c != '\r')
            {
                if (*c == ' ')
                {
                    c++;
                    spaceCount++;
                    continue;
                }
                if (spaceCount == 0)
                {
                   x = *c - '0' + x * 10;
                }
                if (spaceCount == 1)
                {
                   y = *c - '0' + y * 10;
                }
                if (spaceCount == 2)
                {
                   w = *c - '0' + w * 10;
                }
                c++;
            }
            answer.insert(y);
            sumgoal+=w;
            addEdge(y,sink,w,0);
        }

    }

    SA();

    string res;
    char a[20];
    sprintf(a, "%d\n\n",num);
    res = a;  
    for( int i = 0 ; i < num ; i++)
    {
        int len = path[i].size();
        int times = 0;
        while(!path[i].empty())
        {
            int point = path[i].top();
            if(point!=1000&&len==3&&times == 1)
            {
                sprintf(a, "%d %d",point,point);
                res += a;
            }
            else if(point!=1000)
            {
               sprintf(a, "%d",point);
               res += a;
            }
            path[i].pop();
            times++;
            if(!path[i].empty()&&point!=1000)
            {
                sprintf(a, " ");
                res += a;
            }
        }
        if(i!=num-1)
        res += "\n";
    }

    char * topo_file = (char *)res.c_str();
    write_result(topo_file, filename);

	
}
