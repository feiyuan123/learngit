/*#include<stdio.h>
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
}
# include<stdio.h>

int main(void)
{

    enum weekday{sun,mon,tue,wed,thu,fri,sat}day;

            int k;
            printf("input a number(0--6)");
            scanf("%d",&k);
            day=(enum weekday)k;

           //枚举常量与枚举变量比较，输出枚举常量对应的英文字母
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
#include<stdio.h>

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
    printf("please input a number\n");
    scanf("%d",&num);

    printf("the number factorial:%d\n",factorial(num));

    return 0;
}

#include<stdio.h>

int gyf(int ax,int ay)
{
    return(ay==0?ax:gyf(ay,ax%ay));
}

int gy(int cx,int cy)
{
    return(cx>cy?gyf(cx,cy):gyf(cy,cx));
}

int main(void)
{
    int x,y;
    printf("please input two number:\n");
    printf("number A:");
    scanf("%d",&x);
    printf("number B:");
    scanf("%d",&y);

    printf("two number commom measure:%d\n",gy(x,y));

    return 0;
}
*/










































