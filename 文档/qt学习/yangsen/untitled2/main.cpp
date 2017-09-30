#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<ctype.h>
#include<math.h>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<time.h>
using namespace std;
void fre(){freopen("c://test//input.in","r",stdin);freopen("c://test//output.out","w",stdout);}
#define MS(x,y) memset(x,y,sizeof(x))
#define MC(x,y) memcpy(x,y,sizeof(x))
#define MP(x,y) make_pair(x,y)
#define ls o<<1
#define rs o<<1|1
typedef long long LL;
typedef unsigned long long UL;
typedef unsigned int UI;
template <class T1,class T2>inline void gmax(T1 &a,T2 b){if(b>a)a=b;}
template <class T1,class T2>inline void gmin(T1 &a,T2 b){if(b<a)a=b;}
const int N=1<<15,M=0,Z=1e9+7,ms63=1061109567;
int casenum,casei;
UI a[N],b[N];
int n,m,k,x;
int main()
{
    int bit=(1<<15)-1;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        MS(a,0);MS(b,0);
        int tim=(n-1)*m+k;
        while(tim--)
        {
            scanf("%d",&x);
            ++a[x>>15];
            ++b[x&bit];
        }
        int ans=0;
        for(int i=0;i<=bit;++i)
        {
            if(a[i]%m)ans|=i<<15;
            if(b[i]%m)ans|=i;
        }
        printf("%d\n",ans);
    }
    return 0;
}
