/*

#include <stdio.h>
#include<string.h>
//string end '\0' representative null
int main(void)
{

    char str[]="ABC\0DEF";
    //********************************
    memset(str,'\0',sizeof(str));     //memset()function use  ***
    //********************************
    printf("XY\“Z‘1\n");  //string between add '"'use'\"'
    printf("%s\n",str);


//empty string
   // char ns[]=" ";
    //char ns[]={'\0'};
//*********************
    char name[40];        //null occupy one char,actually name just occupy 39 char
    scanf("%s",name);

    printf("%s\n",name);
//*********************

    char ns[]="feifei";
    printf("%-9s\n",ns);     //format output
//**********************

//string array
    int i;
    char cs[3][100];

    printf("please input three string\n");
    for(i=0;i<3;i++){
        printf("cs[%d]=",i);
        scanf("%s",cs[i]);
    }
    for(i=0;i<3;i++)
        printf("cs[%d]=\"%s\"\n",i,cs[i]);
//**************************

    return 0;

}

//string manipulation
#include<stdio.h>

int len_str(const char ns[])
{
    int i=0;
    while(ns[i])
        i++;
    return(i);
}
//subscript
int len_str(const char ns[],int c)
{

    int i=0;
    while(ns[i]!='\0'){
        if(ns[i]==c)
            return(i+1);
        else
            i++;
    }
    return(-1);


}

int main(void)
{
    char str[100];

    printf("please input a string:\n");
    scanf("%s",str);

//printf("the string str[100]=%s,char C subscript:%d\n",str,len_str(str,'c'));

    return 0;
}

//string char c numbers
//9--4??????????????????????????????????????????????????????????????????????????????slove
int len_str(const char ns[],int c)
{
    int i=0,j=0;
    //char cn[100];
   // for(int i=0;i<sizeof(ns);i++)
    while(ns[i]){
         if(ns[i]==c)
             j++;
            //cn[ns[i]-'0']++;
         i++;
    }
    return j;

}

int main(void)
{
    char str[100];

    printf("please input a string:\n");
    scanf("%s",str);

    printf("the string str[100]=%s,char C numbers:%d\n",str,len_str(str,'c'));

    return 0;
}

/*


//numbers of characters
void str_dcount(const char str[],int cnt[])
{
    int i=0;
    while(str[i]){
        if(str[i]>='0' && str[i]<='9')
            cnt[str[i]-'0']++;
        i++;
    }
}

int main(void)
{
    int i;
    int cn[10]={0};
    char str[100];

    printf("input string:\n");
    scanf("%s",str);

    str_dcount(str,cn);

    puts("numbers of characters:\n");
    for(i=0;i<10;i++)
        printf("%d---%d\n",i,cn[i]);

    return 0;
}



//reverse output
#include<stdio.h>
#include<string.h>
int rev_string(const char str[])
{
    int i=0;
    for(i=strlen(str);i>=0;i--)
        printf("%c",str[i]);

}

int main(void)
{
    char str[100];

    printf("input string:\n");
    scanf("%s",str);

    rev_string(str);

    return 0;
}

//ergodic string
unsigned main(void)
{
    char str[100];
    int i=0;
    int no=5;
    printf("input a string:\n");
    scanf("%s",str);

    while(str[i])
        putchar(str[i++]);
    puts("\n");
   // printf("%s\n",str);
    for(int j=0;j<no;j++)
        printf("%s\n",str);
    return 0;
}
void put_char(const char ns[][7],int n)
{
    int i;
    for(i=0;i<n;i++){
        printf("str[%d]=\"",i);

        int j=0;
        while(ns[i][j])
            putchar(ns[i][j++]);

        puts("\"");
    }
}


#include <stdio.h>

int main(void)
{
    char str[][7]={"feifei","haha","yuan"};

    printf("output three strig\n");
    put_char(str,3);

    return 0;
}

//case letter conversion

//#include<ctype.h>
//int toupper(int c)   small-->big
//int tolower(int c)   big-->small

#include<stdio.h>
#include<ctype.h>
unsigned main(void)
{
    int i=0;
    int j=0;
    char str[100];
    printf("input a string:\n");
    scanf("%s",str);

    while(str[i]){
        printf("%c",toupper(str[i]));
        i++;
    }
    putchar('\n');
    while(str[j]){
        printf("%c",tolower(str[j]));
        j++;
    }

    memset(str,'\0',sizeof(str));
    printf("%s\n",str);

    return 0;
}
*/
#include<stdio.h>
#include<ctype.h>
unsigned main(void)
{


    char str[100],str1[100];
    printf("input a string:\n");
    scanf("%s",str);

    for(int i=0,j=0;str[i]!=0;i++){
        if(str[i]>='0' && str[i]<='9')
             continue;
            //memset(str[i],'\0',);
        else{
            str1[j]=str[i];
            j++;
        }
    }
    printf("%s\n",str1);

    return 0;
}

















































