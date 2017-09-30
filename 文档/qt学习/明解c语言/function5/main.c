//#include <stdio.h>
/*#define MI   5
#define FA  -1
//int findn(int vf[],int s,int no)
//{
//    int i=no;
//    vf[0]=s;//sentry
//    while(vf[i]!=s)
//        i--;
//    return i;
//}
//int findn(int vf[],int s,int no)
//{
//    int i=0;
//    vf[no]=s;
//    while (1){
//        if(vf[i]==s)
//            break;
//        i++;
//    }
//    return(i==no?FA:i);
//}
int findn(int vf[],int s,int no)
{
    int i;
    vf[no]=s;
    for(i=0;vf[i]!=s;i++)
        ;
    return(i==no?FA:i);
}

int main(void)
{
    int i,m,key;
    int vc[MI];
    printf("please input a set of numbers\n");
    for(i=0;i<MI;i++){
        printf("vc[%d]=",i+1);
        scanf("%d",&vc[i]);
    }
    printf("please input the number of need find:");
    scanf("%d",&key);
    m=findn(vc,key,MI);
    printf("%d\n",m);
    return 0;
}*/
//Multidimensional array transfer add
/*int mat_add(const int ma[2][3],const int mb[2][3],int mc[2][3])
{
    int i,j;
    for(i=0;i<2;i++)
        for(j=0;j<3;j++)
            mc[i][j]=ma[i][j]+mb[i][j];
return 0;
}*/
//Multidimensional array transfer multiplication one
/*int mat_mul(const int ma[2][3],const int mb[3][2],int mc[2][2])
{
    int i,j,k;
    int temp;
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            temp=0;
            for(k=0;k<3;k++){
                temp+=ma[i][k]*mb[k][j];
            }
            mc[i][j]=temp;
        }
    }
    return 0;
}*/
/*//Multidimensional array transfer multiplication two
int mat_mul(int ma[2][3], int mb[3][2], int mc[2][2])
{
    int i, j, k;
    int temp[2] = {0};
    for(i = 0; i < 2; i++){
        for(k = 0; k < 2; k ++)
            temp[k] = 0;
        for(j = 0; j < 3; j++){//当前行的每个元素
            for(k = 0; k < 2; k++)
                temp[k] += ma[i][j]*mb[j][k];//****
        }
        for(k = 0; k < 2; k++)
            mc[i][k] = temp[k];
    }
    return 0;
}
int main(void)
{
    int i,j;
    int ma[2][3]={{1,2,3},{4,5,6}};
    int mb[3][2]={{1,2},{4,5},{1,1}};
    int mc[2][2]={0};
    //mat_add(ma,mb,mc);
    mat_mul(ma,mb,mc);
    for(i=0;i<2;i++){
        for(j=0;j<2;j++)
        printf("%3d",mc[i][j]);
        printf("\n");
}
    return 0;
}
*/
/*void mat_sum(double ss[6][4])
{
    int i,j;
    printf("sum score:\n");
    for(i=0;i<5;i++)
        for(j=0;j<3;j++)
            ss[i][3]+=ss[i][j];
    for(i=0;i<5;i++)
        printf("%3lf\n",ss[i][3]);
}
void mat_average(double sa[6][4])
{
    int i,j;
    printf("average of three courses:\n");
    for(j=0;j<3;j++)
        for(i=0;i<5;i++)
            sa[5][j]+=sa[i][j];
    for(j=0;j<3;j++)
        printf("%2lf\n",sa[5][j]/5);

}

int main(void)
{
    int i,j;
    double st[6][4]={0};
    printf("please imput each of the students three subjects\n");
    for(i=0;i<5;i++){
        for(j=0;j<3;j++){
            printf("st[%d][%d]=",i+1,j+1);
            scanf("%lf",&st[i][j]);
        }
        putchar('\n');
    }
    mat_sum(st);
    mat_average(st);
    return 0;
}*/
/*int c=0;
void func(void)
{
    static int b=0;
    /*值：静态局部变量如果没有被用户初始化，则会被编译器自动赋值为0，
     * 以后每次调用静态局部变量的时候都用上次调用后的值。这个比较好理解，
     * 每次函数调用静态局部变量的时候都修改它然后离开，
     * 下次读的时候从全局存储区读出的静态局部变量就是上次修改后的值。*/
/*    int        a=0;

    printf("%3d%3d%3d\n",a++,b++,c++);
}


int main(void)
{
    int i;

    puts("  a  b  c");
    puts("------------");
    for(i=0;i<10;i++)
        func();
    puts("------------");

    return 0;
}
*/
/*int ax = 0;

int main()
{
     static int bx =0;
     int cx=0;
     puts("ax bx cx");
     for (int i = 0; i<5; i++) {
         printf("%d%3d%3d\n",ax++,bx++,cx++);

     }
     return 0;
}*/
//#include<stdio.h>
//#include<limits.h>

/*int main()
{
    printf("char     :%d-%d\n",CHAR_MIN,CHAR_MAX);
    printf("short int:%d-%d\n",SHRT_MIN,SHRT_MAX);
    printf("int      :%d-%d\n",INT_MIN ,INT_MAX);
    printf("long int :%d-%d\n",LONG_MIN,LONG_MAX);

    return 0;
}*/
/*
int main(void)
{
    printf("the edition to char system is:");
    if(CHAR_MIN)
        puts("signed");
    else
            puts("unsigned");

    return 0;
}
*/
/*#include<stdio.h>
int main()
{
    unsigned x=12345;
    unsigned long int i;
    x=x&i;
    printf("%u\n",x);

    return 0;
}*/
/*#include<stdio.h>
// unsigned long int m=;
int count_bits(unsigned x)
{

    int count=0;
    while(x){
        if(x &x)
            count++;
        x>>1;
    }
    return (count);
}

int int_bits (void)
{
    return (count_bits(~0u));
}
void print_bits(unsigned x)
{
    int i;
    for (i=int_bits()-1;i>=0;i--)
        putchar(((x>>i)&x)?'1':'0');
}

int main(void)
{
    unsigned na,nb;

    putchar("please input two nonnegative integer");
    printf("integer A:");
    scanf("%lu",&na);
    printf("integer B:",&nb);
    scanf("%u",&nb);

    printf("\nA             =");
    print_bits(na);
    printf("\nB             =");
    print_bits(nb);
    printf("\nA&B           =");
    print_bits(na&nb);
    printf("\nA|B           =");
    print_bits(na|nb);
    return 0;
}
*/
/*
#include<stdio.h>
enum animal  {Dog,Cat,Monkey,Invalid};

void dog(void)
{
    puts("汪汪！！");
}

void cat(void)
{
    puts("喵～！！");
}

void monkey(void)
{
    puts("唧唧！！");
}

enum animal select(void)
{
    int temp;

    do{
        printf("0...狗  1...猫  2...猴  3...结束：");
        scanf("%d",&temp);
    }while(temp<Dog || temp>Invalid);
    return(temp);
}

int main(void)
{
    enum animal selected;

    do{
        switch (selected=select()){
        case Dog       :dog();       break;
        case Cat       :cat();       break;
        case Monkey    :monkey();    break;
        }
    }while(selected !=Invalid);
    return (0);
}
/*
#include<stdio.h>
enum month_element {January=1,February,，December};

void january(void)
{
    puts("spring,summer,autumn,winter");
}

void february(void)
{
    puts("male,female");
}

void april(void)
{
    puts("april");
}

void december(void)
{
    puts("black,white,yellow");
}

enum month_element select(void)
{
    int temp;
    do{
        printf("1...jan  2...feb  3...apr  12...dec  13...invalid");
        scanf("%d",&temp);
    }while(temp<January || temp>Invalid);
    return(temp);
}

int main (void)
{
    enum month_element selected;

    do{
        switch(selected=select()){
        case January     :january();    break;
        case February    :february();   break;

        case April       :april();      break;

        }
    }while(selected!=Invalid);
    return 0;
}*/
# include<stdio.h>

int main(void)
{

    enum weekday{sun,mon,tue,wed,thu,fri,sat}day;

            int k;
            printf("input a number(0--6)");
            scanf("%d",&k);
            day=(enum weekday)k;

           switch(day){


           case sun: printf("sunday\n");break;

           case mon: printf("monday\n");break;

           case tue: printf("tuesday\n");break;

           case wed: printf("wednesday\n");break;

           case thu: printf("thursday\n");break;

           case fri: printf("friday\n");break;

           case sat: printf("satday\n");break;

           default:  printf("input error\n");break;

           }
           return 0;
}









































