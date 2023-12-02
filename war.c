#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
void beap();
struct army
{
    int tanks;
    int planes;
    int soldiers;
};
int main()
{
    int chances;
    struct army army1;
    system("cls");
    srand(time(NULL));
    while (1)
    {

        chances = rand() % 100 + 1;
        printf("\nChances of war are: %d%%\n", chances);

        if (chances > 75)
        {
            printf("\nWar has been started\nEmergency meeting has been called!\n");

            break;
        }
        sleep(1);
    }
    beap();
    army1.tanks = rand() % 100 + 1;
    army1.planes = rand() % 100 + 1;
    army1.soldiers = rand() % 1000 + 1;
    int count = 1;
    printf("\n\nArmy has been deployed\n");
    printf("Tanks: %d\nPlanes: %d\nSoldiers: %d\n", army1.tanks, army1.planes, army1.soldiers);
    sleep(2);
    while (army1.planes > 0 || army1.soldiers > 0 || army1.tanks > 0)
    {
        int num = rand() % 50;
        int num1 = rand() % 50 ;
        int num2 = rand() % 300;
        //Winning condition
        int winning = rand() % 100 + 1;
        if(winning > 85)
        {
            printf("\n\nArmy has won the war on Day %d\n", count);
            printf("The Remaining items are:\nTanks: %d\nPlanes: %d\nSoldiers: %d\n", army1.tanks, army1.planes, army1.soldiers);
            printf("Base has been defended successfully!\n");
            return 0;
        }
        sleep(1);
        army1.tanks -= num;
        army1.planes -= num1;
        army1.soldiers -= num2;

        if (army1.planes < 0)
        {
            army1.planes = 0;
        }
        if (army1.soldiers < 0)
        {
            army1.soldiers = 0;
        }
        if (army1.tanks < 0)
        {
            army1.tanks = 0;
        }
        printf("\n");

        printf("\n\nDay %d : \nTanks: %d \nPlanes: %d\nSoldiers: %d\n", count, army1.tanks, army1.planes, army1.soldiers);
        
        count++;
    }
    printf("\nAll the army has been killed\n");
    printf("Base has been captured\n");
    


    return 0;
}

void beap()
{
    int count = 05;
repeat:
    Beep(1000, 500);
    count--;
    if (count > 0)
    {
        goto repeat;
    }
}