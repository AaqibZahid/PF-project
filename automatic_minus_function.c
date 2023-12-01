#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main() {
    system("cls");
    int count = 1;
    int provisions[2] = {50 , 100}; 
    srand(time(NULL));
    while (provisions[0] > 0 && provisions[1] > 0)
    {
        int num = rand() % 10 + 1;
        provisions[0] -= num;
        provisions[1] -= num;
        if (provisions[0] < 0)
        {
            provisions[0] = 0;
        }
        if (provisions[1] < 0)
        {
            provisions[1] = 0;
        }
        
        
        printf("Provisions Remaining Day %d : \nTanks: %d \nPlanes: %d\n",count, provisions[0], provisions[1]);
        sleep(1);
        count++; 
    }
    printf("All provisions are gone\n");
    printf("Base has been captured\n");
    
    
    return 0;
}