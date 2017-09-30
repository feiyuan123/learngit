/*
//point leap year
#include <stdio.h>

void yesterday(int *y,int *m,int *d)
{
    int month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(--*d==0){
        if(--*m==2)
            *d=28+(*y%400==0 || *y%4==0 && *y%100!=0);
        else if(*m==0){
            (*y)--;
            *m=12;
            *d=31;
        }
        else *d=month[*m];
    }
}


void tomorrow(int *y,int *m,int *d)
{
    int month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    month[2]+=(*y%400==0 || *y%4==0 && *y%100!=0);
    if(++*d>month[*m]){
        *d=1;
        if(++*m>12){
            *m=1;
            (*y)++;
        }
    }
}

int main(void)
{
    int i;
    int year,month,date,y,m,d;
    printf("please input now year month date : ");
    scanf("%d,%d,%d",&year,&month,&date);
    y=year;
    m=month;
    d=date;

    yesterday(&year,&month,&date);
    printf("yesterday %d,%d,%d",year,month,date);

    tomorrow(&y,&m,&d);
    printf("tomorrow %d,%d,%d",y,m,d);

    return 0;
}


//point ordered arrangment
void sort3(int *n1,int *n2,int *n3)
{
    int temp,i;
    for(i=0;i<3;i++){
        if(*n1>*n2){
            temp=*n1;
            *n1=*n2;
            *n2=temp;
        }
        if(*n2>*n3){
            temp=*n2;
            *n2=*n3;
            *n3=temp;
        }
    }
}

int main(void)
{
    int a,b,c;
    printf("input three numbers :");
    scanf("%d,%d,%d",&a,&b,&c);

    sort3(&a,&b,&c);
    printf("%d,%d,%d",a,b,c);

    return 0;
}
*/

#include<stdio.h>
int main(void)
{
    int i;
    int vc[5]={10,20,30,40,50};
    int *ptr=&vc[0 ];             //*ptr is else name to vc[0]

    for(i=0;i<5;i++)
        printf("vc[%d]=%d  ptr[%d]=%d  *(ptr+%d)=%d\n",i,vc[i],i,ptr[i],i,*(ptr+i));
    //if vc[0] address is 500,next element vc[1] save address is 500+sizeof(int)            //***
    //ptr+2 point to vc[2],add pointer operators * so *(ptr+2) is else name to vc[2]
    //vc[2]=2[vc]=*(ptr+2)=ptr[2]=2[ptr]
    //***********************************************************************************
        return 0;
}










































