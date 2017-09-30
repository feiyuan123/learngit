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
Edge edge[55000000];
int head[MAXN], edgenum, cur[MAXN];
int pre[MAXN];
int dist[MAXN];
bool vis[MAXN];
stack<int> path[MAXN],path2[MAXN];
//shuchu road
int road[MAXN];
int cnt,Mina;
//test
int consumer[MAXN];
//#define N     30
/*
#define T     3500    
#define EPS   1e-8   
#define DELTA 0.95    
#define LIMIT 130  
#define OLOOP 500
#define ILOOP 500
*/
int T;     
#define eps   1e-38
#define DELT 0.95
#define DELT1 0.8
#define LIMIT 130
#define OLOOP 500
#define ILOOP 20
#define T1 7

double t,t1;
set<int>answer,answertemp;
set<int>curP,newP;
clock_t start;
clock_t finish;
void init()
{
    edgenum = 0;
    sumgoal = 0;
    memset(head, -1, sizeof(head));
    memset(consumer, 0 , sizeof(consumer));
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
    int sam=0,cut=0;
    deque<int> Q;
    CLR(dist, INF);
    CLR(vis, false);
    CLR(pre, -1);
    vis[s] = true; dist[s] = 0; Q.push_back(s);
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop_front();
        if(dist[u]*cut>sam)
        {
            Q.push_back(u);
            continue;
        }
        sam -= dist[u];cut--;
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
                    if(!Q.empty())
                    {
                        if(dist[E.to]>dist[Q.front()])
                            Q.push_back(E.to);
                        else
                            Q.push_front(E.to);
                    }
                    else
                    Q.push_back(E.to);
                    sam += dist[E.to];cut++;
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
        //while(!path[num].empty()) path[num].pop();
        int Min = INF;
        for( i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            Edge E = edge[i];
            Min = min(Min, E.cap - E.flow);
        }
        path[num].push(Min);
        for(i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
          //  path[num].push(edge[i].from);
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            //cout << edge[i].cost << endl;
            cost += edge[i].cost * Min;
        }
        flow += Min;

        num++;
    }
}

void MCMFtest(int s, int t, int &flow, int &cost)
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
        for(i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            path[num].push(edge[i].from);
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            //cout << edge[i].cost << endl;
            cost += edge[i].cost * Min;
        }
        flow += Min;
        path[num].push(Min);
        num++;
    }
}

set<int> Next(set<int> p)
{
    int i,ta;
    set<int> ans = p;
    int k = ans.size();
    set<int>::iterator it;
    int z = (int)(2 * (rand() / (RAND_MAX + 1.0)));
    //int x = (int)(k * (rand() / (RAND_MAX + 1.0)));
    if(t1<1) ta = 1;
    else ta = t1;
    for( i = 0 ; i < int(ta) ; i++)
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

set<int> GetNext1(set<int> p)
{
    int i,flag1,flag2,flag3;
    flag1=0;
    flag2=0;
    flag3=0;
    set<int> ans = p;
    int k = ans.size();
    if(k==K)
        flag1=1;
    else if(k<K&&k>0)
        flag2=1;
    else if(k==0)
        flag3=0;
    set<int>::iterator it;
    int z = (int)(2 * (rand() / (RAND_MAX + 1.0)));
   // int x = (int)(k * (rand() / (RAND_MAX + 1.0)));
    if(flag1||(flag2&&z==0))
    {
        for( i = 0 ; i < 1 ; i++)
        {
            it = ans.begin();
            int y = (int)(k * (rand() / (RAND_MAX + 1.0)));
                while(y--)
                {
                    it++;
                }
                ans.erase(it);
                k--;

        }
    }
    else if(flag3||(flag2&&z==0))
    {
        for( i = 0 ; i < 1 ; i++)
        {
            it = ans.begin();
            int g = *it;
            while(ans.find(g)!=ans.end())
            {
                it = answertemp.begin();
                int y = (int)(K * (rand() / (RAND_MAX + 1.0)));
                while(y--)
                {
                    it++;
                }
                g = *it;
            }
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
    int i,number = 0,flag,temp;
    set<int>::iterator it;
    for( it = a.begin() ; it!=a.end(); it++)
    {
        flag=0;
        for(i = head[source]; i != -1; i = edge[i].next)
        {
            if(edge[i].to ==*it)
            {
                temp = i;
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            addEdge(source,*it,INF,0);
        }
        else
        {
            edge[temp].cap=INF;
        }
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
int calc1(set<int> a)
{
    int i,temp,number = 0,flag;
    set<int>::iterator it;
    for( it = a.begin() ; it!=a.end(); it++)
    {
        flag = 0;
        for( i = head[source]; i != -1; i = edge[i].next)
        {
            if(edge[i].to ==*it)
            {
                temp = i;
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            addEdge(source,*it,INF,0);
        }
        else
        {
            edge[temp].cap=INF;
        }
        number++;
    }
    int flow, cost;
    MCMF(source, sink, flow, cost);
    if(flow == sumgoal)
        return number*ServiceCost+cost;
    else
        return -1;
}

void SA()
{
     t = T;
     t1 = T1;
    srand(time(NULL));
    int time = 0;
    curP = answer;
    newP = answer;
    double len2 = calc(curP);
   // int P_L = 0;
    int P_F = 0;
    while(1)
    {
        for(int i = 0; i < ILOOP; i++)
        {
            newP= Next(curP);
            double len1 = calc(newP);

            if(len1!=-1)
            {
              //  double len2 = calc(curPath);
                double dE = len1 - len2;
                if(dE==0)
                {
                    time++;
                }
                else
                {
                    time=0;
                }
                if(time==15)
                {
                    answer = curP;
                    break;
                }
                if(dE < 0)
                {
                    curP = newP;
                    len2=len1;
                //  P_L = 0;
                 //  P_F = 0;
                }
                else
                {
                    dE=0-dE;
                    double rd = rand() / (RAND_MAX + 1.0);
                //    double x = exp(dE / t);
                    if(exp(dE / t) > rd && exp(dE / t) < 1)
                    {
                        curP = newP;
                        len2 = len1;
                    }
                  // P_L++;
                }
            }
/*
            if(P_L > LIMIT)
            {
                P_F++;
                break;
            }
*/
            finish = clock();
            if(((finish - start) / CLOCKS_PER_SEC)>86)
            {
                 //answer = curPath;

                if(calc(curP) < calc(answer))
                    answer = curP;

                break;
            }
        }
        if(time==15)
        {
            break;
        }
        if(((finish - start) / CLOCKS_PER_SEC)>86)
{
             answer = curP;
            break;
}
/*
        if(calc(curPath) < calc(answer))
            answer = curPath;
*/

        if(P_F > OLOOP || t < eps)
{
             answer = curP;
            break;
}
        t *= DELT;
        t1*= DELT1;

    }

}
void output()
{
   while(!path[num].empty()) path[num].pop();
    while(!path2[num].empty()) path2[num].pop();
   for(int i = cnt-2 ; i >=1 ; i--)
   {
      path[num].push(road[i]);
      path2[num].push(road[i]);
   }
   path[num].push(Mina);
   path2[num].push(Mina);
   num++;
}
bool writeroadDFS(int s,int t, int step)
 {
     if(s==t)
     {
         cnt = step;
         output();
     //    Mina=INF;
         return true;
     }
     for(int i = head[s]; i != -1; i = edge[i].next)
     {
         Edge E = edge[i];
         if(E.flow>0&&!vis[E.to])
         {
             vis[E.to]=1;
             road[step] = E.to;
             pre[E.to] = i;
             //int temp = Mina;
             Mina = min(E.flow,Mina);
             if(writeroadDFS(E.to,t,step+1))
                return true;
             vis[E.to]=0;
            // Mina=temp;
         }
     }
     return false;
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
    for(  int i = 4 ; i < line_num ; i++)
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
            consumer[y] = x;
            //test:
            answer.insert(y);
            sumgoal+=w;
            addEdge(y,sink,w,0);
        }

    }
    answertemp=answer;

 //   answer=GetNext1(answer);
    if(N<170)
    {
        T=400;
    }
    else
    {
        T=1;
    }
    SA();
 //   cout<<"count:"<<iterative<<endl;
    calc1(answer);
    num = 0;
    memset(vis , 0 , sizeof(vis));
    CLR(pre, -1);
    Mina=INF;
    vis[source]=1;
    while(writeroadDFS(source,sink,1))
   {
        for(int i = pre[sink]; i != -1; i = pre[edge[i^1].to])
        {

            edge[i].flow -= Mina;
            edge[i^1].flow -= Mina;

        }
        memset(vis , 0 , sizeof(vis));
        CLR(pre, -1);
        Mina=INF;
   }

    string res;
    char a[20];
    sprintf(a, "%d\n\n",num);
    res = a;
    for( int i = 0 ; i < num ; i++)
    {
        int minflow = path2[i].top();
        path2[i].pop();
        while(!path2[i].empty())
        {
            int point = path2[i].top();
            if(path2[i].size()==1)
            {
                sprintf(a, "%d %d %d",point,consumer[point],minflow);
                res += a;
            }
            else
            {
               sprintf(a, "%d",point);
               res += a;
            }
            path2[i].pop();
            if(!path2[i].empty())
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
