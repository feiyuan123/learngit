#include "deploy.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <set>
#include <math.h>
using namespace std;

#define MAX_LINE_LEN 55000

#define INLINE  static __inline
#ifdef _DEBUG
#define PRINT   printf
#else
#define PRINT(...)
#endif

#define INF 0x3f3f3f3f  
#define min(a,b) (a>b?b:a)
#define CLR(a, b) memset(a, (b), sizeof(a))
//网络流初始化参数 
int N,M,K,ServiceCost,text;//N表示起始ID，M表示终止ID，K表示总带宽大小，ServiceCost表示单位网络租赁费
int source, sink,sumgoal,number,num; 
 
struct Edge  
{  
    int from, to, cap, flow,cost, next;  
};  
Edge edge[550000]; 
int head[MAXN], edgenum, cur[MAXN];  
int cost[MAXN][MAXN],costpoint[MAXN],pre[MAXN];
int dist[MAXN];  
bool vis[MAXN]; 
stack<int> path[MAXN];
//退火初始化参数
//#define N     30      //城市数量
#define T     3500    //初始温度
#define EPS   1e-8    //终止温度
#define DELTA 0.95    //温度衰减率
#define LIMIT 130  //概率选择上限
#define OLOOP 500   //外循环次数
#define ILOOP 500  //内循环次数
set<int>answer;
set<int>curPath,newPath;

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
	int temp = -1,time=0;
    while ((cnt < spec) && !feof(fp))
    {
        line[0] = 0;
        if (fgets(line, MAX_LINE_LEN + 2, fp) == NULL)
			continue;
        if (line[0] == 0)
			continue;
		if (line[0]==10)
		{
			if(time==2)
				temp = cnt;
			time++;
		}
        buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
        strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
        buff[cnt][MAX_LINE_LEN + 1] = 0;
        cnt++;
    }
	int x,y,w,f;
	N = atoi(strtok(buff[0]," "));
	M = atoi(strtok(NULL," "));
	K = atoi(strtok(NULL," "));
	ServiceCost =  atoi(strtok(buff[2]," "));

	
	for( unsigned int i = 4 ; i < cnt ; i++)
	{
		if(i<temp)
		{
			x = atoi(strtok(buff[i]," "));
			y = atoi(strtok(NULL," "));
			w = atoi(strtok(NULL," "));
			f = atoi(strtok(NULL," "));
		//	addEdge(x,y,w,f);
			addEdge1(x,y,w,f);
			addEdge1(y,x,w,f);
		}
		else if(i>temp)
		{
			x = atoi(strtok(buff[i]," "));
			y = atoi(strtok(NULL," "));
			w = atoi(strtok(NULL," "));
			costpoint[x] = y;
			answer.insert(y);
			sumgoal+=w;
			addEdge(y,sink,w,0);
		}		
	}
	
    fclose(fp);
}

void getMap()  
{  
	int i;
//	int server[]={43,38,37,22,15,13,44,34};
	//cost:2462
//	int server[]={15,22,34,37,38,43,44};
	//cost:2610
//	int server[]={7,13,15,38,44};
	//cost:2692
//	int server[]={13,15,34,37,38,43,44};
//	cost:2584
//	int server[]={7,15,22,34,38};
	//cost:2933
//	int server[]={15,34,38,37};
//	int server[]={15,34,38,37};
	//cost:3261
//	int server[]={7,13,15,22,37,38,43};
	//cost:2042
//	int server[]={7,13,15,22,37,38};
//	cost:2092
//	int server[]={15,43,39,3};
	//cost:2690
	int server[]={43,0,22,37,13,15,38};
	//cost:2231
//	int server[]={0,3,22};
	number = sizeof(server)/sizeof(server[0]);
//	int num  = sizeof(server);
	/*
    for( i = 1; i <= N; i++)  
    {  
        if((i + j) & 1)//T集 连汇点 权值为该点的权值  
            addEdge((i-1)*M + j, sink, Map[i][j]);  
        else  
        {  
            addEdge(source, (i-1)*M + j, Map[i][j]);//源点 连S集权值为该点的权值  
            if(j > 1)  
                addEdge((i-1)*M + j, (i-1)*M + j - 1, INF);//S集连T集  
            if(j < M)  
                addEdge((i-1)*M + j, (i-1)*M + j + 1, INF);  
            if(i > 1)  
                addEdge((i-1)*M + j, (i-2)*M + j, INF);  
            if(i < N)  
                addEdge((i-1)*M + j, i*M + j, INF);  
        }   
    }*/
	for( i = 0 ; i < number ; i++)
	{
 		addEdge(source,server[i],INF,0);
	}
} 
/*
bool BFS(int s, int t)  
{  
    queue<int> Q;  
    memset(dist, -1, sizeof(dist));  
    memset(vis, false, sizeof(vis));  
    dist[s] = 0;  
    vis[s] = true;  
    Q.push(s);  
    while(!Q.empty())  
    {  
        int u = Q.front();  
        Q.pop();  
        for(int i = head[u]; i != -1; i = edge[i].next)  
        {  
            Edge E = edge[i];  
            if(!vis[E.to] && E.cap > E.flow)  
            {  
                dist[E.to] = dist[u] + 1;  
           
                if(E.to == t) return true; 
				     vis[E.to] = true;  
                Q.push(E.to);  
            }  
        }  
    }  
    return false;  
}  

int DFS(int x, int a, int t)  
{  
    if(x == t || a == 0) return a;  
    int flow = 0, f;  
    for(int &i = cur[x]; i != -1; i = edge[i].next)  
    {  
        Edge &E = edge[i];  
        if(dist[E.to] == dist[x] + 1 && (f = DFS(E.to, min(a, E.cap-E.flow), t)) > 0)  
        {  
            edge[i].flow += f;  
            edge[i^1].flow -= f;  
            flow += f;  
            a -= f;  
            if(a == 0) break;  
        }  
    }  
    return flow;  
}  

int Maxflow(int s, int t)  
{  
    int flow = 0;  
    while(BFS(s, t))  
    {  
        memcpy(cur, head, sizeof(head));  
        flow += DFS(s, INF, t);  
    }  
    return flow;  
} 
bool check()
{
	int ans = 0;
	getMap();
	ans = Maxflow(source, sink);
	if(ans==sumgoal)
		return true;
	else
		return false;
}
*/

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
			path[num].push(E.from);
            Min = min(Min, E.cap - E.flow);
        }
        for(i = pre[t]; i != -1; i = pre[edge[i^1].to]) 
		{
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


//退火函数部分
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
		
		/*
		while(x == y)
		{
		x = (int)(n * (rand() / (RAND_MAX + 1.0)));
		y = (int)(n * (rand() / (RAND_MAX + 1.0)));
		}
		*/
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
	while(1)       //外循环，主要更新参数t，模拟退火过程
	{
		for(int i = 0; i < ILOOP; i++)    //内循环，寻找在一定温度下的最优值
		{
			newPath = GetNext(curPath);
			double len1 = calc(newPath);
			 len1 = calc(newPath);
			if(len1!=-1)
			{
				double len2 = calc(curPath);
				double dE = len1 - len2;
				if(dE < 0)   //如果找到更优值，直接更新
				{
					curPath = newPath;
					P_L = 0;
					P_F = 0;
				}
				else
				{
					double rd = rand() / (RAND_MAX + 1.0);    
					if(exp(dE / t) > rd && exp(dE / t) < 1)   //如果找到比当前更差的解，以一定概率接受该解，并且这个概率会越来越小
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
	}
	set<int>::iterator it;
	for( it = answer.begin() ; it!=answer.end(); it++)
	{
		if( it==answer.begin())
			cout<<*it;
		else
			cout<<" "<<*it;
	}
	cout<<endl;
	cout<<calc(answer)<<endl;
	cout<<num<<endl;
	for( i = 0 ; i < num ; i++)
	{
		while(!path[i].empty())
		{
			int point = path[i].top();
			if(point!=1000)
			cout<<point<<" ";
			path[i].pop();
		}
		cout<<endl;
	}
}

//You need to complete the function 
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
	init(); 
	read_file1(topo, MAX_EDGE_NUM, filename);
	printf("%d %d %d %d\n",N,M,K,ServiceCost);
//	printf("%d %d %d %d\n",edge[0].from,edge[0].to,edge[0].cap,cost[edge[0].from][edge[0].to]);
	/*
	getMap();
	int flow, cost;
    MCMF(source, sink, flow, cost);
	printf("flow:%d cost:%d\n",flow,number*ServiceCost+cost);
	*/
/*	if(check())
		printf("YES\n");
	else
		printf("NO\n");
		*/
	SA();
/*
	// Output demo
	char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

	write_result(topo_file, filename);
*/

}
