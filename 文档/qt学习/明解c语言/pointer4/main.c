/*#include <stdio.h>

int str_char(const char *str, char c);

int main(void)
{
    char st[128];
    char ch;

    printf("please enter a string: ");
    scanf("%s", st);

    while (getchar() != '\n')
        ;

    printf("please enter a character: ");
    scanf("%c", &ch);

    printf("the character '%c' have %d in the string \"%s\"\n",
        ch, str_char(st, ch), st);

    return 0;
}

int str_char(const char *str, char c)
{
    int cnt = 0;

    while (*str)
        if (c == *str++)
            cnt++;

    return cnt;
}

#include <stdio.h>

char *str_toupper(char *str);
char *str_tolower(char *str);

int main(void)
{
    char st[128];
    int c;
    printf("please enter a string: ");
    scanf("%s", st);
    do {
        printf("0...upper 1...lower 2...quit: ");
        scanf("%d", &c);

        switch (c) {
        case 0: printf("the upper string is \"%s\"\n",
                str_toupper(st));
            break;
        case 1: printf("the lower string is \"%s\"\n",
                str_tolower(st));
            break;
        case 2: printf("quit...\n");
            break;
        default: break;
        }
        if (c == 2)
            break;
    } while (1);

    return 0;
}

char *str_toupper(char *str)
{
    char *t = str;

    while (*str) {
        if (*str >= 'a' && *str <= 'z')
            *str += 'A' - 'a';
        str++;
    }

    return t;
}

char *str_tolower(char *str)
{
    char *t = str;                                   //*****************************

    while (*str) {
        if (*str >= 'A' && *str <= 'Z')
            *str += 'a' - 'A';
        str++;
    }

    return t;
}
*/
#include <stdio.h>
#include <string.h>

char *del_digit(char *str);

int main(void)
{
    char st[128];

    printf("please enter a string: ");
    scanf("%s", st);

    puts("delete the digit from string");
    printf("the delete digit string is \"%s\"\n", del_digit(st));

    return 0;
}


char *del_digit(char *str)
{
    char *t = str;                 //***************指向str字符串的第一个字符，str经过处理变化了，*t也就变了
    char *p = str;                 //***************

    //××××××××××××××××××××××××××××××××××××××××
    while (*str){
        if (*str >= '0' && *str <= '9')
            str++;
        else                                        //？？？？？？？？？？？？？？？？？？
            *p++ = *str++;
    *p = '\0';
    }
   //×××××××××××××××××××××××××××××××××××××××××
    return t;
}
