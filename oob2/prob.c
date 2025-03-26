#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include "/home/choi/hackingchamp/prob/aa.h"

#define Null 0
#define _GNU_SOURCE

char name[40] = "hIdd3n";
char* skill_text[4] = {"Feel the power of the elements!","Unleash the fury of the dragon!","Prepare to face my ultimate attack!"};
int skill_1 = 0;
int skill_2 = 0;
struct information 
{
    char user_name[10];
    char user_name2[10];
};

static inline uint64_t readfsqword(uint32_t offset)
{
     uint64_t value;
    __asm__ __volatile__("movq %%fs:%1, %0"
                         : "=r"(value)
                         : "m"(*(uint64_t *)(offset)));
    return value;
}

void set();
void start();
void hp(struct information* user, int team1_hp, int team2_hp);
void win(struct information* user,int a);
unsigned int select_skill_number();
int select_skill();
int custom_skill_1(const char *a);
int custom_skill_2(const char *a);
int custom_skill_3(const char *a);
int ultimate_skill();
int create_team(struct information* user);
ssize_t play(struct information* user);

void (*skillTable[3])() = {custom_skill_1,custom_skill_2,custom_skill_3,ultimate_skill};

int main()
{   
    set();
    srand(time(NULL));

    struct information* user = (struct information*)malloc(sizeof(struct information));

    start();

    while(1){
        play(user);
    }
}

void set()
{
    setvbuf(stdin,0,2,0);
    setvbuf(stderr,0,2,0);
}

void start()
{
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⢷⣷⣣\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⢏⣿⣿⡵⡀\n");
    printf("⠀⠀⠀⠀⣠⣮⣷⣿⣿⣿⣿⣷⣄⣄⠀⠀⠀⠀⠈⢞⣿⣿⡵⡀\n");
    printf(" ⠀⠀⡠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣏⢦⣤⡀⠀⠀⠀⠫⣻⣿⣾⢄\n");
    printf(" ⠀⣔⣿⣿⣿⣿⣿⣿⠿⣿⠻⢟⣿⣿⣿⣿⣿⡆⠀⠀⠀⠑⡿⣿⣯⢆\n");
    printf(" ⢰⣸⢿⣻⢟⠃⠉⠉⠀⡠⠤⠸⣸⣿⣿⣿⡳⠁⠀⠀⠀⠀⡨⠺⠿⠇⢓⡄\n");
    printf(" ⠧⠊⠁⠘⣖⣳⠠⣶⣋⡹⠁⠀⠛⣩⢻⠋⠀⠀⠀⠀⠀⢀⠇⠀⠀⠀⠀⢾\n");
    printf("⠀⠀⢠⠂⠁⠓⠒⠊⠀⡠⠤⡀⢠⠀⠚⠀⠀⠀⠀⠀⡠⠊⢀⠤⡤⣔⠩⠼⡀\n");
    printf("⠀⠀⢇⠀⠀⢀⡠⢔⣪⠠⠖⠇⡘⠀⠀⠀⢀⠄⠒⠉⢀⠔⠁⠀⣧⢞⠮⠭⠵⡀\n");
    printf("⠀⠀⠘⠒⠉⣾⣀⣀⠀⣀⣀⠦⠗⠹⠙⠃⠁⠀⡠⠔⡡⠔⠒⠉⡨⢴⢹⣿⣏⡆\n");
    printf("⠀⠀⠀⠀⡸⠉⠀⠀⠁⠀⠀⠀⠀⣇⡠⡄⡶⠯⠔⠈⠀⠀⡠⠊⠀⠀⡿⣿⣿⡇\n");
    printf("⠀⠀⠀⢀⠇⠀⠀⠀⠀⢀⣀⠤⡤⠵⠊⢸⠀⡠⠤⠤⠐⠉⠀⠀⠀⠀⣷⣿⢿⡇\n");
    printf("⠀⠀⢀⠃⠀⢀⣀⣀⣀⣠⣀⣀⣿⠉⠉⠉⠉\n");
    printf("  Gogildong Game!\n\n\n");
}



void win(struct information* user,int a)
{
    if(a == 1)
    {
        printf("Team %s win!\n",user->user_name);
    }
    else
    {
        printf("Team %s win!\n",user->user_name2);
    }
}

int custom_skill_1(const char *a)
{
    printf("attack by skill_1!\n");
    return puts(a);
}
int custom_skill_2(const char *a)
{
    printf("attack by skill_2!\n");
    return puts(a);
}
int custom_skill_3(const char *a)
{
    printf("attack by skill_3!\n");
    return puts(a);
}
int ultimate_skill()
{
    printf("congrats!\n%s\n", getenv("flag"));
    exit(0);
    
}


void hp(struct information* user, int team1_hp, int team2_hp)
{
    printf("===================================\n");
    printf("%s hp : %d\n",user->user_name,team1_hp);
    printf("%s hp : %d\n",user->user_name2,team2_hp);
    printf("===================================\n\n");
}

int create_team(struct information* user)
{
    printf("Team1 : ");
    scanf("%s",user->user_name);
    getchar();

    printf("Team2 : ");
    scanf("%s",user->user_name2);
    getchar();

    if(strcmp(user->user_name,user->user_name2)==0)
    {
        printf("[-]The name is duplicate\n");
        printf("Please re-enter\n");
        return 0;
    }
    else
    {
        printf("\n[+]It has been put on\n\n");
        return 1;
    }
}


ssize_t play(struct information* user)
{

    int number = 0;
    int skill_num = 0;
    int team1_hp = 50;
    int team2_hp = 50;
    int random_attack = 0;


        while(number==0)
        {
            number = create_team(user);
            team1_hp = 50;
            team2_hp = 50;
        }

    while(1)
    {
        hp(user,team1_hp,team2_hp);
        skill_num = select_skill();
            
        if(skill_num == 1)
        {
            select_skill_number();
            skillTable[skill_1](skill_text[skill_1]);
        }
        else if(skill_num == 2)
        {
            skill_1 = rand() % 3;
            skillTable[skill_1](skill_text[skill_1]);
        }
        random_attack = rand() % (30-10+1)+10;
        team1_hp -= random_attack;
        if(team1_hp<=0)
        {
            win(user,1);
            break;
        }

        sleep(1);
        printf("\n");

        skillTable[skill_2](skill_text[skill_2]);

        random_attack = rand() % (30-10+1)+10;
        team2_hp -= random_attack;

        if(team2_hp<=0)
        {
            win(user,2);
            break;
        }
    }
    
    printf("Please enter the name you wish : \n");
    
    return read(0,name,40);
}

int select_skill()
{
    char y_n;

    
    while(y_n!='y'&& y_n!='n' && y_n!='Y' && y_n!='N')
    {
        printf("select skill (y/n)? : ");
        scanf("%c",&y_n);
        getchar();
        

        if(y_n!='y' && y_n!='n' && y_n!='Y' && y_n!='N')
        {
            printf("Please enter only yes or no\n");
        }
    }

    if(y_n=='y'||y_n=='Y')
    {
        return 1;
    }
    else if(y_n=='n' || y_n=='N')
    {
        return 2;
    }
    return 0;
}

unsigned int select_skill_number()
{
    unsigned int re;
    int skill_select;

    re = readfsqword(40);
    while(1)
    {
        printf("skill number : ");
        scanf("%d",&skill_select);
        getchar();
        if(skill_select<=3)
        {
            break;
        }
        printf("please select skill number 1~3\n");
    }
    skill_1 = skill_select - 1;
    printf("skill change!\n\n");
    
    skill_2 = rand() % 3;

    return readfsqword(40) ^ re;
}
