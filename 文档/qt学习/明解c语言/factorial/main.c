/*#include<stdio.h>

int factorial(int n)
{
    if(n>0)
        return(n*factorial(n-1));
    else
        return 1;
}

int main(void)
{
    int num;
    printf("please input a number:");
    scanf("%d",&num);
    printf("the number common measure %d\n",factorial(num));

    return 0;

#include <stdio.h>

int a[100]={0};
int combination(int x,int y)
{
    if(y==1){
        a[y-1]=x;
        int j=0;
        while(a[j]!=0){
             j++;
        }
        for(int i=j-1;i>=0;i--)
            printf("%d,",a[i]);

        printf("\n");
    }
    else{
        a[y-1]=x;
        for(int j=x-1;j>=y-1;j--)
            combination(j,y-1);
    }
    return 0;
}

int main(void)
{
    int n=6;
    int r=3;

    for(int i=n;i>=r;i--){
        combination(n,r);
    }

    return 0;
}
*/

/*#include<stdio.h>

int factorial(int n)
{
    if(n>0)
        return(n*factorial(n-1));
    else
        return 1;
}

int main(void)
{
    int num;
    printf("please input a number:");
    scanf("%d",&num);
    printf("the number common measure %d\n",factorial(num));

    return 0;

#include <stdio.h>

int a[100]={0};
int combination(int x,int y)
{
    if(y==1){
        a[y-1]=x;
        int j=0;
        while(a[j]!=0){
             j++;
        }
        for(int i=j-1;i>=0;i--)
            printf("%d,",a[i]);

        printf("\n");
    }
    else{
        a[y-1]=x;
        for(int j=x-1;j>=y-1;j--)
            combination(j,y-1);
    }
    return 0;
}

int main(void)
{
    int n=6;
    int r=3;

    for(int i=n;i>=r;i--){
        combination(n,r);
    }

    return 0;
}






void fp(int begin,int end)
{
    if(begin<end)
       fp(begin,end-1);
    printf("%3d",end);

   /* printf("%3d",begin);
    if(begin<end)
        fp(begin+1,end);

}

int main(void)
{

    fp(0,10);

    return 0;
}

int sum(int begin,int end)
{
    if(begin==end)
        return begin;
    return(begin+sum(begin+1,end));
}

int main(void)
{
    printf("%d\n",sum(0,100));
    return 0;
}


#include<stdio.h>
#include<string.h>

int fr(char* p,char* q)
{
    if(p>=q)
            return;//exit
    char t=*p;     //simple task
        *p=*q;
         *q=t;

    fr(p+1,q-1);   //similer task
}

int main(int argc,char* argv[])
{
    char s[]="12345678";
    printf("%d\n",s+strlen(s)-1);

    fr(s,s+strlen(s)-1);//???s+strlen(s)-1就是字符串的末尾地址
    printf("%s\n",s);

    return 0;

}

//××××××××××××××××××××××××××××××××××××××××××××××××××××××


#include "stdio.h"
#define MAX 100

void combine(int a[], int n, int m, int b[], int M)
{
 int i, j;

 for (i = n; i >= m; i--)
  {
   b[m - 1] = i - 1;                //simple task
   if (m > 1)                       //similer task
    combine(a, i - 1, m - 1, b, M);
   else                            //exit
    {
     for (j = M - 1; j >= 0; j--)
      printf("%d ", a[b[j]]);
     printf("\n");
    }
  }
}

int main(void)
{
 int i;
 int a[MAX]={0};
 int b[MAX]={0};

 for (i = 1; i < 100; i++)
  a[i - 1] = i;

 combine(a, 5, 4, b, 4);
}

//×××××××××××××××××××××××××××××××××××××××××××××××××××××××××



#include <stdio.h>

int main(void)
{
    int i,ch;
    int cou[10]={0};
    while(1)
    {
        ch=getchar();
        if(ch==EOF)             //linux：EOF keyboard output is  ctrl+d
                                //windos:                        ctrl+z
        break;
        switch(ch){
        case'0':cou[0]++;  break;
        case'1':cou[1]++;  break;
        case'2':cou[2]++;  break;
        case'3':cou[3]++;  break;
        case'4':cou[4]++;  break;
        case'5':cou[5]++;  break;
        case'6':cou[6]++;  break;
        case'7':cou[7]++;  break;
        case'8':cou[8]++;  break;
        case'9':cou[9]++;  break;
        }
    }
    puts("numbers char counts");
    for(i=0;i<10;i++)
        printf("'%d':%d\n",i,cou[i]);

    return 0;
}


#include <stdio.h>

int main(void)
{
    int i,j,ch;
    int cou[10]={0};
    while(1)
    {
        ch=getchar();
        if(ch==EOF)             //linux：EOF keyboard output is  ctrl+d
                                //windos:                        ctrl+z
        break;
        else
       //********************************************
       //     if(ch>=48 && ch<=57) //JIS code table
       //         cou[ch-48]++;
       //*********************************************
            // can portability enhance
            if(ch>='0' && ch<='9')
                 cou[ch-'0']++;
       //********************************************
       /* switch(ch){
        case 48:cou[0]++;  break;
        case 49:cou[1]++;  break;
        case 50:cou[2]++;  break;
        case 51:cou[3]++;  break;
        case 52:cou[4]++;  break;
        case 53:cou[5]++;  break;
        case 54:cou[6]++;  break;
        case 55:cou[7]++;  break;
        case 56:cou[8]++;  break;
        case 57:cou[9]++;  break;
        }
    }
    puts("numbers char counts");
    for(i=0;i<10;i++){
        printf("'%d':",i);
        for(j=0;j<cou[i];cou[i]--)
            putchar('*');
        printf("\n");
    }

    return 0;
}
/*
#include<stdio.h>
int main(void)
{
    int i,ch;
    printf("%d\n",EOF);
    for(i=0;i<10;i++)
        printf("'%d'---%d\n",i,'0'+i);
    return 0;
}

//copy input to output
#include <stdio.h>
int main(void)
{
    int ch;
    while((ch=getchar())!=EOF)
        putchar(ch);
    return 0;
}


#include<stdio.h>
int main(void)
{
    int i=0,ch;

    while((ch=getchar())!=EOF){
         if(ch=='\n')
             i++;
    }

    printf("%d\n",i);

    return 0;
}

*/







































