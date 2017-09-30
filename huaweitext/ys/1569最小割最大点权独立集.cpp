#include <cstdio>  
#include <cstring>  
#include <queue>  
#include <stack>  
#include <vector>  
#include <algorithm> 
#define min(a,b) (a>b?b:a) 
#define MAXN 3000  
#define MAXM 20000+10  
#define INF 0x3f3f3f3f  
#define LL long long  
using namespace std;  
struct Edge  
{  
    int from, to, cap, flow, next;  
};  
Edge edge[MAXM];  
int head[MAXN], edgenum, cur[MAXN];  
int dist[MAXN];  
bool vis[MAXN];  
int N, M;  
int source, sink;  
int Map[60][60];  
int sum;  
void init()  
{  
    edgenum = 0;  
    memset(head, -1, sizeof(head));  
}  
void addEdge(int u, int v, int w)  
{  
    Edge E1 = {u, v, w, 0, head[u]};  
    edge[edgenum] = E1;  
    head[u] = edgenum++;  
    Edge E2 = {v, u, 0, 0, head[v]};  
    edge[edgenum] = E2;  
    head[v] = edgenum++;  
}  
void getMap()  
{  
	int i,j;
    sum = 0;  
    for(i = 1; i <= N; i++)  
    {  
        for( j = 1; j <= M; j++)  
            scanf("%d", &Map[i][j]), sum += Map[i][j];  
    }  
    source = 0, sink = 2501;  
    for( i = 1; i <= N; i++)  
    {  
        for( j = 1; j <= M; j++)  
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
        }  
    }  
}  
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
                vis[E.to] = true;  
                if(E.to == t) return true;  
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
int main()  
{  
    while(scanf("%d%d", &N, &M) != EOF)  
    {  
        init();  
        getMap();  
        printf("%d\n", sum - Maxflow(source, sink));  
    }  
    return 0;  
}  