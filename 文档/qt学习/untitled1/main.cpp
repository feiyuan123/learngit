#include<stdio.h>
main(){
    FILE *fp;
    char ch;
    if((fp=fopen("/home/zhangfeifei/文档/qt学习/untitled1/result.txt","rt"))==NULL){
        printf("\nCannot open file strike any key exit!");
        //getch();
        //exit(1);
    }
    ch=fgetc(fp);
    while(ch!=EOF){
        putchar(ch);
        ch=fgetc(fp);
    }
    fclose(fp);
}
