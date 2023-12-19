#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void set();
void menual();
int go();
void create_dia(int page, char arr[10][11]);
void write_dia(int page, char arr[10][11]);
int read_dia(int page,char arr[10][11]);
void list(int page, char arr[10][11]);

char arr_data[10][100];

int main()
{
    set();

    while(1)
    {
        if (go() == 4)
            break;
    }
    printf("bye\n");
    return 0;
}

void set()
{
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
}

void menual()
{
    printf("1.Create_diary\n");
    printf("2.Write_diary\n");
    printf("3.read_diary\n");
    printf("4.exit\n\n");
}

int go()
{
    char arr[10][11];

    int number = 0;
    int page = 0;

    while(number != 4)
    {
        menual();

        printf("index : ");
        scanf("%d",&number);

        switch(number){
            case 1:
                if(page > 9)
                {
                    printf("Exceeded\n");
                    return 4;
                }

                create_dia(page,arr);

                page += 1;
                break;
            case 2:              
                write_dia(page,arr);
                break;
            case 3:
                read_dia(page,arr);
                break;
            case 4:
                return 4;
            default:
                getchar();
                break;
        }
    }
}

void create_dia(int page, char arr[10][11])
{
    printf("\ninput diary title (%d/10)\n",page+1);
    printf("index : ");

    scanf("%10s",arr[page]);
    getchar();
}

void write_dia(int page, char arr[10][11])
{
    int number = 0;

    list(page,arr);
    printf("index : ");
    scanf("%d",&number);
    
    printf("title : %s\n",arr[number-1]);
    printf(">>> ");
    scanf("%99s",arr_data[number-1]);
    getchar();
}

int read_dia(int page,char arr[10][11])
{
    char v2[40];
    int number = 0;
    char v3[7] = "hIdd3n";
    list(page,arr);

    printf("index : ");
    scanf("%d",&number);
    if(!strcmp(arr[number-1],v3))
    {
        printf("how did you find it...\n");
        printf(">>> ");
        scanf("%60s",v2);
        printf("??? : %s\n",v2);
        return 0;
    }

    printf("text : %s\n\n",arr_data[number-1]);

}

void list(int page, char arr[10][11])
{
    printf("\n==select diary number==\n");
    for(int i = 1; i<=page ; i++)
    {
        printf("%d.%s\n",i,arr[i-1]);
    }
    printf("=======================\n\n");
}