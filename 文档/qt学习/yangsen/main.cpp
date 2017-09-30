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

void fre() { freopen("c://test//input.in", "r", stdin); freopen("c://test//output.out", "w", stdout); }
#define MS(x, y) memset(x, y, sizeof(x))
#define ls o<<1
#define rs o<<1|1
typedef long long LL;
typedef unsigned long long UL;
typedef unsigned int UI;
template <class T1, class T2>inline void gmax(T1 &a, T2 b) { if (b > a)a = b; }
template <class T1, class T2>inline void gmin(T1 &a, T2 b) { if (b < a)a = b; }
const int N = 0, M = 0, Z = 1e9 + 7, inf = 0x3f3f3f3f;
template <class T1, class T2>inline void gadd(T1 &a, T2 b) { a = (a + b) % Z; }
int casenum, casei;
int n;

void datamaker_pre()
{
    srand(time(0));
    freopen("Skip the Class_pre.in", "w", stdout);
    casenum = 1000; printf("%d\n", casenum);
    for (casei = 1; casei <= casenum; ++casei)
    {
        int n = rand() % 10 + 1; printf("%d\n", n);
        for (int i = 1; i <= n; ++i)
        {
            int l = rand() % 3 + 1;
            for (int j = 0; j < l; ++j)printf("%c", rand() % 5 + 'a');
            int v = rand() % 1000 + 1;
            printf(" %d\n", v);
        }
    }
}
void datamaker()
{
    srand(time(0));
    freopen("Skip the Class.in", "w", stdout);
    casenum = 1000; printf("%d\n", casenum);
    for (casei = 1; casei <= casenum; ++casei)
    {
        int n = rand() % 100 + 1; printf("%d\n", n);
        for (int i = 1; i <= n; ++i)
        {
            int l = rand() % 3 + 1;
            for (int j = 0; j < l; ++j)printf("%c", rand() % 5 + 'a');
            int v = rand() % 1000 + 1;
            printf(" %d\n", v);
        }
    }
}
int main()
{
    datamaker_pre(); //return 0;
    freopen("Skip the Class_pre.in", "r", stdin); freopen("Skip the Class_pre.out", "w", stdout);
  //  datamaker(); return 0;
    scanf("%d", &casenum);
    for (casei = 1; casei <= casenum; ++casei)
    {
        map<string, int> first, second;
        first.clear();
        second.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            char s[12]; int v;
            scanf("%s%d", s, &v);
            gmax(second[s], v);
            if (second[s] > first[s])swap(second[s], first[s]);
        }
        int sum = 0;
        map<string, int> ::iterator it;
        for(it=first.begin();it!=first.end();it++)
        {
            sum+=it->second;
        }
        for(it=second.begin();it!=second.end();it++)
        {
            sum+=it->second;
        }
        printf("%d\n", sum);
    }
    return 0;
}
