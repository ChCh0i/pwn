#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set()
{
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
}

void flag()
{
    system("/bin/sh");
}

void menual()
{
    printf("1.Create diary\n");
    printf("2.Write_read diary\n");
    printf("3.list\n");
    printf("4.exit\n");
}

void list(int page,char arr[5][13])
{
    for(int i = 0; i<page; i++)
    {
        printf("%d. %s\n",page,arr[i]);
    }
}

int go()
{
    char arr[5][13] = {};
    

    int a = 0;
    int page = 0;
    do
    {
        menual();
        
        printf("index : ");
        scanf("%d",&a);
        
        switch(a)
        {
            case 1:
                if(page>4)
                {
                    printf("diary pull!\n");
                    return 4;
                }
                create_dia(page,arr);

                page+=1;
                break;
            case 2:
                write_dia(page,arr);
                break;
            case 3:
                list(page,arr);
                break;
            case 4:
                return 4;
            default:
                getchar();
                break;
        }
    }while(a != 4);
}
void create_dia(int page,char arr[5][13])
{
    printf("please input diary title (%d/5)\n",page);

    if(page<=0)
    {
        printf("you not create diary\n");
    }

    if(page>=0)
    {
        printf(">>> ");
        scanf("%s",arr[page]);
        getchar();
    }
}
void write_dia(int page,char arr[5][13])
{
    char buf[0x100];
    int number = 0;

    while(1)
    {
        list(page,arr);

        printf(">>> ");
        scanf("%d",&number);

        if(number > 0 && number <= page)
        {
            read(0,buf,0x100);
            printf("your saved diary\n");
            if(strcmp(arr[number-1],"admin")==0)
            {
                printf(buf);
                exit(0);
            }
            printf("buf : %s\n",buf);
        }
    }
}

int main()
{
    set();

    while(1)
    {
        if(go()==4)
        {
            break;
        }
    }
    printf("bye\n");
}
