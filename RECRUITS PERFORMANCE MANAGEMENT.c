#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
int main(){
	char rank;

    printf("Enter your rank (M for Major, C for Colonel, L for Lieutenant): ");
    scanf(" %c", &rank);
	//Change exercises according to army camp
    switch(rank) {
        case 'M':
        case 'm':
            printf("Welcome Major! Here are your drills and tasks:\n");
            Sleep(500);//Pauses for 0.5s

            printf("Tanks Maintainance\n");
            Sleep(200);//Nice effect in display!!!
            printf("50 Pushups\n");
            Sleep(200);
            printf("Combat strategy\n");
            Sleep(200);
            break;
        case 'C':
        case 'c':
            printf("Welcome Colonel! Here are your drills and tasks:\n");
            Sleep(500);
            printf("Leadership training\n");
            Sleep(200);
            printf("Strategy Layout\n");
            Sleep(200);
            printf("Battlefield coordination\n");
            Sleep(200);
            break;
        case 'L':
        case 'l':
            printf("Welcome Lieutenant! Here are your drills and tasks:\n");
            Sleep(500);
            printf("Basic training\n");
            Sleep(200);
            printf("Field exercises\n");
            Sleep(200);
            printf("Team coordination\n");
            Sleep(200);
            break;
        default:
            printf("\nInvalid rank entered. Please enter M, C, or L.\n");
            Sleep(200);
            break;
        
    }
    return 0;
}
