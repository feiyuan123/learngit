#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
#include <time.h>
#include <math.h>
using namespace std;
typedef int EdgeType;
#define MAXVEX 2000
#define INFINITY 6555535
#define GROUPNUM 121

int P[102][2000];
typedef struct EdgeNode
{
	int adjvex;
	int numBian;
	EdgeType weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct
{
	int Gen[102];
	int GenLen;
	int Dic[2000];
	double adapt;
	int dis;
}GROUP;

typedef struct VertexNode
{
	int in;	//入度
	int data;
	EdgeNode *firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct 
{
	AdjList adjList;
	int numVertexes,numEdges;
}GraphAdjList;

typedef struct
{
	int demand[200];
	int nDemand;
}Demand;

GROUP G[GROUPNUM];//父代
GROUP gen_next[GROUPNUM];//子代
double varp=0.9;
int dic[2000];
class Map
{
public:
	Demand dem1;
	Demand dem2;
	GraphAdjList* map;
	int tsp[2000][2000];
public:
	Map();
	~Map();
	void Totsp();
	void SPFA(int v0,int num, int *D);
	void ReadMap();
	void TopologicalSort();
};


Map::Map()
{
	map = new GraphAdjList;
}

Map::~Map()
{
	delete map;
}
void Map::ReadMap()
{
	FILE *fp = fopen("topo.csv","r");
	if (fp == NULL)
	{
		return ;
	}
	EdgeNode* e;
	char line[60];
	char demand_c[600];
	int i, j, temp = 0;
	for (i=0; i < MAXVEX; i++)//顶点表
	{
		map->adjList[i].in = 0;
		map->adjList[i].data = i;
		map->adjList[i].firstedge = NULL;
	}
	while(fgets(line, sizeof(line),fp))
	{
		map->numEdges = atoi(strtok(line, ","));

		i = atoi(strtok(NULL, ","));
		j = atoi(strtok(NULL, ","));
		map->adjList[j].in++;
		if (i>map->numVertexes || j>map->numVertexes)
			map->numVertexes = i>j?i:j;
		e = new EdgeNode;
		e->adjvex = j;
		e->numBian = map->numEdges;
		e->next = map->adjList[i].firstedge;
		map->adjList[i].firstedge = e;
		e->weight = atoi(strtok(NULL, ","));
	
	}
	map->numVertexes++;	
	fclose(fp);


	FILE *fp1 = fopen("demand.csv","r");
	if (fp1 == NULL)
	{
		return ;
	}
//	fgets(demand_c, sizeof(demand_c), fp1);
	memset(demand_c, 0, sizeof(demand_c));
	fgets(demand_c, sizeof(demand_c), fp1);
//	strtok(demand_c, ",");
	dem1.demand[0] = atoi(strtok(demand_c, ","));
	dem1.demand[1] = atoi(strtok(NULL, ","));
	i = 2;
	while (1)
	{
		char* temp;
		temp = strtok(NULL, "|");
		if (NULL == temp)
			break;
		else
		{
			dem1.demand[i] = atoi(temp);	
			i++;	
		}
	}
	dem1.nDemand=i;
}

void Map::SPFA(int v0,int num, int *D)
{
	int vis[2000];
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(v0);
	vis[v0] = 1;
	EdgeNode *temp;
	D[v0] = 0;
	while(!q.empty())
	{
		int next = q.front();
		q.pop();
		vis[next] = 0;
		temp = map->adjList[next].firstedge;
		while(temp)
		{
			if (dic[temp->adjvex]!=0)
			{
				temp = temp->next;
				continue;
			}
			if (D[next]+temp->weight < D[temp->adjvex])
			{
				D[temp->adjvex] = D[next]+temp->weight;
				P[num][temp->adjvex] = next;
				if (!vis[temp->adjvex])
				{
					vis[temp->adjvex] = 1;
					q.push(temp->adjvex);
					
				}
			}
			temp = temp->next;
		}
	}
	
}

void Map::TopologicalSort()
{
	EdgeNode *e;
	stack<int> s;
	int i,k,gettop;
	int top = 0;
	int count = 0;
	
	for(i=0;i<map->numVertexes;i++)
		if (map->adjList[i].in == 0)
			s.push(i);
	while (!s.empty())
	{
		gettop = s.top();
		s.pop();
		if (gettop == dem1.demand[0])
			continue;
		cout<<map->adjList[gettop].data<<"->";
		for (e=map->adjList[gettop].firstedge; e; e=e->next)
		{
			k=e->adjvex;
			if (!(--map->adjList[k].in))
				s.push(k);
		}
	}
}


void Map::Totsp()
{
	int i,j;
	int D[2000];
	int path[2000];
	tsp[0][0] = INFINITY;
	for (i=0;i<dem1.nDemand;i++)
		dic[dem1.demand[i]]++;
	for (i=0;i<	dem1.nDemand; i++)
	{
		dic[dem1.demand[i]]--;
		for(j=1;j<dem1.nDemand; j++)
		{
			dic[dem1.demand[j]]--;
			if (i == 1 || i==j)
			{
				
					tsp[i][j] = INFINITY;
			//		printf("%d ",tsp[i][j]);
				
			}
			else
			{
				fill(D,D+2000,65535);
				memset(path,-1,sizeof(path));
				SPFA(dem1.demand[i],i,D);		
				tsp[i][j] = D[dem1.demand[j]];
			//		printf("%d ",tsp[i][j]);
				
			}
			dic[dem1.demand[j]]++;
		}
		dic[dem1.demand[i]]++;
	//	printf("\n");
	}
}



//GA
int haxi[2000];



int TotalDistance2(Map *graph, int *random)
{
	int N = graph->dem1.nDemand;
	int count=0,start,end;
	memset(dic,0,sizeof(dic));
	int distance=0;
	distance+=graph->tsp[0][random[2]];
	start=graph->dem1.demand[0];
	end=graph->dem1.demand[random[2]];
	dic[start]++;
	while(P[0][end]!=-1)
	{
		dic[P[0][end]]++;
		if(dic[P[0][end]]>1)
			count++;
		end=P[0][end];
	}
	distance+=graph->tsp[random[N-1]][1];
	start=graph->dem1.demand[random[N-1]];
	end=graph->dem1.demand[1];
	dic[start]++;
	dic[end]++;
	while(P[random[N-1]][end]!=-1)
	{
		dic[P[random[N-1]][end]]++;
		if(dic[P[random[N-1]][end]]>1)
			count++;
		end=P[random[N-1]][end];
	}
	for (int i=2;i<N-1;i++)
	{
		distance+=graph->tsp[random[i]][random[i+1]];
		start=graph->dem1.demand[random[i]];
		end=graph->dem1.demand[random[i+1]];
		dic[start]++;
		while(P[random[i]][end]!=-1)
		{
			dic[P[random[i]][end]]++;
			if(dic[P[random[i]][end]]>1)
				count++;
			end=P[random[i]][end];
		}
	}
	
    return distance+40*count;
}

void short_path(Map* graph,int v0,int* path, int *D)
{
	int vis[2000];
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(v0);
	vis[v0] = 1;
	EdgeNode *temp;
	D[v0] = 0;
	while(!q.empty())
	{
		int next = q.front();
		q.pop();
		vis[next] = 0;
		temp = graph->map->adjList[next].firstedge;
		while(temp)
		{
			if (haxi[temp->adjvex]!=0)
			{
				temp = temp->next;
				continue;
			}
			if (D[next]+temp->weight < D[temp->adjvex])
			{
				D[temp->adjvex] = D[next]+temp->weight;
				path[temp->adjvex] = next;
				if (!vis[temp->adjvex])
				{
					vis[temp->adjvex] = 1;
					q.push(temp->adjvex);
					
				}
			}
			temp = temp->next;
		}
	}
	
}

long TotalDistance1(Map* graph,int *random)
{
	long distance=0;
	int N = graph->dem1.nDemand;
	distance += graph->tsp[0][random[2]];
	distance += graph->tsp[random[N-1]][1];
	for (int i=2;i<N-1;i++)
	{
		distance += graph->tsp[random[i]][random[i+1]];
	}
	return distance;
}
int vex[1000];

int n;//路径总结点个数
int quan(Map* graph, int *random)
{ 
	memset(dic,0,sizeof(dic));
	int distance = 0;
	int p[2000];
	int D[2000];
	int N=graph->dem1.nDemand;
	int start = graph->dem1.demand[0];
	int end;
	int temp;
	stack<int> vt;
	n=0;
	memset(vex,-1,sizeof(vex));
	//vex[n]=start;
//	dic[start]++;
//	n++;
	for (int i=2; i<N+1; i++)
	{	
		if (i == N)
			end = graph->dem1.demand[1];
		else
			end = graph->dem1.demand[random[i]];
		fill(D,D+2000,65535);
		memset(p,-1,sizeof(p));
		short_path(graph,start,p,D);
		temp = D[end];
	//	printf("%d ",temp);
			distance+=temp;
			
		if (i==N)
			temp = graph->dem1.demand[1];
		else
			temp = graph->dem1.demand[random[i]];
		while (p[temp] != -1)
		{
		
			vt.push(p[temp]);
			temp = p[temp];
		}		
		while(!vt.empty())
		{
			vex[n] = vt.top();
			haxi[vt.top()]++;
			vt.pop();
			n++;
		}		
	//	vex[n]=end;
	//	dic[end]++;
		start = end;
	//	n++;

		
	}
	return distance;
}

int best=INFINITY;
int bestPath[300];
int bestsolution = 0 ;
void judge(Map* graph)//随机评价
{
	int i;
	int best_temp = INFINITY;
	double sumDistance=0;
	double sumP=0,temp=0;
	int N=graph->dem1.nDemand;
	for(i=0;i<GROUPNUM;i++)
	{
	
		gen_next[i].adapt = TotalDistance1(graph,gen_next[i].Gen);		
		gen_next[i].dis = TotalDistance2(graph,gen_next[i].Gen);
		if (gen_next[i].dis <best)
		{	
				best = gen_next[i].adapt;
				memcpy(bestPath,gen_next[i].Gen,N*sizeof(int));
			
		}
		sumDistance+=gen_next[i].adapt;
	}

	for (i=0; i<GROUPNUM; i++)
	{
		gen_next[i].adapt = 1/gen_next[i].adapt;
		sumP+=gen_next[i].adapt;
		if (gen_next[i].adapt > temp)
		{
			temp = gen_next[i].adapt;
			bestsolution=i;
		}
	}
	temp=0;
	sumP -= gen_next[bestsolution].adapt;
	for (i=0; i<GROUPNUM; i++)
	{
		if(i==bestsolution)
			continue;
		gen_next[i].adapt = gen_next[i].adapt/sumP;
		temp+=gen_next[i].adapt;
		//cout<<temp<<" ";
	//	printf("%f\n",gen_next[i].adapt);
	}
//	printf("gen:%d\n",TotalDistance1(gen_next[GROUPNUM-1].Gen));
	//cout<<endl;
	
}


void cross2(Map* graph)
{
	int i,j;
	int loc1,loc2;
	int temp1,temp2;
	int gen1[102]={0};
	int gen2[102]={0};
	gen_next[GROUPNUM-1]=G[0];
//	printf("%d\n",TotalDistance1(	gen_next[GROUPNUM-1].Gen));

	for (i=0;i<29;i++)
		gen_next[i] = G[i];
	for(i=29;i<GROUPNUM-1;i+=2)
	{

		memset(gen1,0,sizeof(gen1));
		memset(gen2,0,sizeof(gen2));
		if (graph->dem1.nDemand==3)
		{
			loc1 = loc2 = 2;
		}
		else
		{
			do
			{
				loc1 = 2+rand()%(graph->dem1.nDemand-2);
				loc2 = 2+rand()%(graph->dem1.nDemand-2);
			}
			while(loc1==loc2);
			if (loc1>loc2)
				swap(loc1,loc2);
		}

		for(j=loc1;j<=loc2;++j)               
		{
		    temp1 = gen_next[i].Gen[j] = G[i+1].Gen[j];
		    temp2 = gen_next[i+1].Gen[j] = G[i].Gen[j];
		    gen1[temp1] = temp2;               
		    gen2[temp2] = temp1;
		}
	
		for(j=0;j<loc1;++j)                    
		{
		    temp1 = G[i].Gen[j];
		    while(gen1[temp1]!=0)              
		        temp1 = gen1[temp1];
		     gen_next[i].Gen[j] = temp1;

		    temp2 = G[i+1].Gen[j];
		    while(gen2[temp2]!=0)              
		        temp2 = gen2[temp2];
		    gen_next[i+1].Gen[j] = temp2;
		}

		for(j=loc2+1;j<graph->dem1.nDemand;++j)                    
		{
		    temp1 = G[i].Gen[j];
		    while(gen1[temp1]!=0)              
		        temp1 = gen1[temp1];
		    gen_next[i].Gen[j] = temp1;

		    temp2 = G[i+1].Gen[j];
		    while(gen2[temp2]!=0)              
		        temp2 = gen2[temp2];
		    gen_next[i+1].Gen[j] = temp2;
		}	
	}
//	printf("gen:%d\n",TotalDistance1(gen_next[GROUPNUM-1].Gen));

}

void var(Map *graph)
{
	int N = graph->dem1.nDemand; 
	int i;
	int temp1,temp2,temp3;
	double pvar;
	int count=0;
	for(i=0;i<GROUPNUM;i++)
	{
		pvar = rand()/(RAND_MAX+1.0);
		if (pvar<varp)
		{
			count++;
			if (N == 3)
			{
				temp1 = 2;
				temp2 = 2;
			}
			else
			{
				do
				{
					temp1=2+rand()%(N-2);
					temp2=2+rand()%(N-2);
				}
				while(temp1==temp2);
			}
			temp3=gen_next[i].Gen[temp2];
			gen_next[i].Gen[temp2]=gen_next[i].Gen[temp1];
			gen_next[i].Gen[temp1]=temp3;
			//swap(gen_next[i].Gen[temp1],gen_next[i].Gen[temp2]);
		}
	
	}
	//	printf("%d\n",count);
//	cout<<endl;
//		printf("gen:%d\n",TotalDistance1(gen_next[GROUPNUM-1].Gen));
}

void get_newpath(int N,int *random)
{
	int temp1,temp2,temp3;
	do
	{
		temp1=2+rand()%(N-2);
		temp2=2+rand()%(N-2);
	}
	while(temp1==temp2);

	temp3=random[temp1];
	random[temp1]=random[temp2];
	random[temp2]=temp3;
}

void gen_sel(Map *graph)
{
	int i,j;
	double gradient[GROUPNUM];
	double ran;
	memset(gradient,0,sizeof(gradient));
	if(0==bestsolution)
		gradient[0]=0;
	else
		gradient[0] = gen_next[0].adapt;

	for(i=1;i<GROUPNUM;i++)
	{
		if(i==bestsolution)
		{
			gradient[i] = gradient[i-1];
			continue;
		}
		gradient[i] = gen_next[i].adapt+gradient[i-1];
	}
	
	G[0] = gen_next[bestsolution];
	for(i=1;i<GROUPNUM;i++)
	{
		ran = rand()/(RAND_MAX+1.0); 

		for(j=0;j<GROUPNUM;j++)
		{
			if(ran<gradient[i])
			{
					G[i] = gen_next[0]; 
					break;
			}
		}
	}

}

void randPath(int N,int *random)
{

	int ran = 0;
	int i,j;
	for (i=2;i<N;i++)
	{
		
		ran = 2+rand()%(N-2);
		for(j=2;j<i;j++)
		{
			if (ran == random[j])
				break;
		}	
		if (j < i)
		{
			i--;
			continue;
		}
		random[i] = ran;
	}
	
}

void init_group(Map* graph)
{
	int i;
	int N = graph->dem1.nDemand;
	for (i=0;i<GROUPNUM;i++)
		memset(G[i].Gen,-1,200*sizeof(int));
	for (i=0; i<GROUPNUM;i++)
	{
		randPath(N,G[i].Gen);
		G[i].Gen[0]=0;
		G[i].Gen[1]=1;
	}
			
}

void GA(Map* graph)
{

	
	best=INFINITY;
	int bestD=INFINITY;
	int nNode,nRep=0;
	int path[500];
	int qua ;
	int i;
	varp=0.85;

	init_group(graph);
	int red;
	for(red=0;red<12000;red++)
	{
		cross2(graph);
		var(graph);
		judge(graph);	
		//printf("best:%d\n",best);
		gen_sel(graph);
	}
	qua = quan(graph,bestPath);
	
	if(qua<bestD)
	{
		bestD=qua;
		nNode = n;
		memcpy(path,vex,n*sizeof(int));
	}
	printf("qua:%d\n",qua);
	for(i=0;i<nNode;i++)
		printf("%d ",path[i]);			
}

int SA(Map *graph)
{
	int N = graph->dem1.nDemand;
	double INIT_T = 400;
	double T = INIT_T;
	double RATE = 0.98;
	double FINAL_T = 1E-10;
	int IN_LOOP = 8000;
	int OUT_LOOP = 2000;
	int P_LIMIT = 300000;
	int vex_old[202];
	int vex_new[202];
	int path[202];
	int best = INFINITY,temp;
	int P_t=0,A_t=0;
	int old_distance,best_distance=INFINITY,new_distance;
	int delta;
	int gain = 400;
	randPath(graph->dem1.nDemand,vex_new);
	old_distance = TotalDistance1(graph,vex_new);
	
	while (true)
	{
	//	P_t=0;
	//	memcpy(vex_new,path,sizeof(int)*N);
	/*	if ( gain >=1 )
		{
			if(gain<=20)
				gain = 1;
			else
				gain -=20;

		}*/
		for (int i=1;i<=IN_LOOP;i++)
		{
			memcpy(vex_old,vex_new,N*sizeof(int));
			get_newpath(N, vex_old);
			new_distance = TotalDistance1(graph,vex_old);
			delta = new_distance - old_distance;
		//	temp = TotalDistance2(graph,vex_old);
		//	if ( temp < best)
		//	{
	//			best = temp;
		//		memcpy(path,vex_old,N*sizeof(int));
	//		}
			if (new_distance<best_distance)
			{
				best_distance = new_distance;
				memcpy(path,vex_old,N*sizeof(int));
			}
			if (delta < 0)
			{
				old_distance = new_distance;
			//	printf("%d\n",old_distance);
				memcpy(vex_new,vex_old,N*sizeof(int));
				P_t = 0;
				A_t = 0;
				
			}

			else 
			{
				double ran = rand()%1000/1000.0;
				double pg =exp(-delta/T);
				if (pg > ran)
				{
					old_distance = new_distance;
					memcpy(vex_new,vex_old,N*sizeof(int));
				}
				
					P_t++;
			}
		//	printf("best:%d,now:%d\n",best_distance,old_distance);
			if (P_t>P_LIMIT)
			{
				A_t++;
				break;
			}

		}
	//	if (old_distance < best_distance)
	//	{
	//		best_distance = old_distance;
	//		memcpy(path,vex_new,N*sizeof(int));
	//	}
		printf("best_distance:%d\n",best_distance);
		if ( T < FINAL_T || A_t>OUT_LOOP)
			break;
	
		T = T*RATE;
	}
	int qua = quan(graph,path);
	printf("qua:%d\n",qua);
	return 0;
}

void main()
{
	srand(time(NULL));
	int D[2000];
	int path[2000];
	fill(D,D+2000,65535);
	memset(path,-1,sizeof(path));
	Map* graph = new Map;
	graph->ReadMap();
//	short_path(graph,7,path,D);
//	graph->SPFA(7,path,D);
//	cout<<D[13];
	memset(P,-1,102*2000*sizeof(int));
	graph->Totsp();
	SA(graph);;
//	GA(graph);

}
