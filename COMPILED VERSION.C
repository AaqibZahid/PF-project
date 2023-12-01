//DEFINING LIBRARIES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
//DEFINING STRUCTURES
struct Task 
{
    int number;
    char description[100];
};
struct Soldier 
{
    char name[50];
    int rank;
    struct Task *tasks;
    int numTasks;
};
typedef struct users {
	char fname[50];
	char lname[50];
	char rank[50];
	char password[50];
}users;
struct base
{
    char rank[50], officialname[50], baselocation[50], destination[50];
    int baseduration, base_strength;
};
//FUNCTIONS PROTOTYPE
void password ();
void provideTasks(struct Soldier soldier);
int validateRank(int rank);
void saveDetails(users user[], int i, FILE *fptr);
int adduser ();
void savingbaseinfotofile(struct base b1, int baseID);
int updatenewbase(int base_id);
int registernewbase();
int viewexistingbase(int baseID);
void encryptor(FILE *fptr);
void decryptor (FILE *fptr);
//FUNCTIONS DEFINITION
void password ()
{
	int password = 54321, cnt = 0, i, userpassword;
	printf("Welcome to BaseOps Pro!\nEnter the password: ");
	for (i=1; i<=3; i++)
	{
		scanf("%d", &userpassword);
		if(userpassword != password)
		{
			if(i == 1 || i == 2){
				printf("\nYou have entered wrong password!\nTry Again.... (%d tries left)\n", 3-i);
			}
			if(i == 3){
				printf("\nUnauthorized Access Alert!!!\nSystem Criticality Compromised!!!");
			}
		}
		else
		{
			printf("Correct! Welcome...");
			break;
		}
	}
}
void provideTasks(struct Soldier soldier) 
{
	int i;
    printf("Welcome, %s!\n", soldier.name);
    printf("Your rank is %d. Here are your tasks:\n", soldier.rank);
    for (i = 0; i < soldier.numTasks; i++) 
	{
        printf("%d. %s\n", soldier.tasks[i].number, soldier.tasks[i].description);
    }
}
int validateRank(int rank) 
{
    if (rank < 1 || rank > 6) 
	{
        return 0;
    }
    return 1;
}
void savingbaseinfotofile(struct base b1, int baseID)
{
    char filename[20];
    sprintf(filename, "Base_Ops_Pro_Base_Info_%d.txt", baseID); // Will Create a file with the name Base_Ops_Pro_Base_Info_(baseID).txt
    FILE *file;
    file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Base ID: %d\n", baseID);
    fprintf(file, "Rank: %s\n", b1.rank);
    fprintf(file, "Official Name: %s\n", b1.officialname);
    fprintf(file, "Base Location: %s\n", b1.baselocation);
    fprintf(file, "Destination: %s\n", b1.destination);
    fprintf(file, "Base Duration: %d minutes\n", b1.baseduration);
    fprintf(file, "Base Strength: %d\n", b1.base_strength);

    fclose(file);
}
int updatenewbase(int base_id)
{

    char filename[20];
    sprintf(filename, "Base_Ops_Pro_Base_Info_%d.txt", base_id);
    FILE *file;
    if (access(filename, F_OK) != -1)
    {
        // File exists
        FILE *file = fopen(filename, "w");

        if (file == NULL)
        {
            printf("Error opening file for editing!\n");
            return 0;
        }

        struct base b1;
        char rankoption;
        printf("\n\nUpdating Base\n\n");
        printf("\nEnter your rank: ");
        printf("\n1. Colonel ---> C\n2. Lieutenant ---> L\n3. Major ---> M\n");
        scanf(" %c", &rankoption);

        if (rankoption == 'C' || rankoption == 'c')
        {
            strcpy(b1.rank, "Colonel");
        }
        else if (rankoption == 'L' || rankoption == 'l')
        {
            strcpy(b1.rank, "Lieutenant");
        }
        else if (rankoption == 'M' || rankoption == 'm')
        {
            strcpy(b1.rank, "Major");
        }
        else
        {
            printf("\nInvalid Option Entered!\nExiting The Program\n");
            return 0;
        }
        printf("\nYour rank is: %s (FOR TESTING PURPOSE ONLY)", b1.rank);
        printf("\nEnter your name: ");
        fflush(stdin);
        gets(b1.officialname);
        printf("\nEnter the location of your base: ");
        fflush(stdin);
        gets(b1.baselocation);
        printf("\nEnter the base duration(in minutes): ");
        if (scanf("%d", &b1.baseduration) != 1)
        {
            printf("\nInvalid Base Duration Entered!\n\n");
            return 0;
        }
        printf("\nEnter the strength of your base: ");
        if (scanf("%d", &b1.base_strength) != 1)
        {
            printf("\nInvalid Base Strength Entered!\n\n");
            return 0;
        }
        printf("\nEnter the destination of your base: ");
        scanf("%s", b1.destination);
        fprintf(file, "Rank: %s\n", b1.rank);
        fprintf(file, "Official Name: %s\n", b1.officialname);
        fprintf(file, "Base Location: %s\n", b1.baselocation);
        fprintf(file, "Destination: %s\n", b1.destination);
        fprintf(file, "Base Duration: %d minutes\n", b1.baseduration);
        fprintf(file, "Base Strength: %d\n", b1.base_strength);
        printf("\nYour base has been updated Successfully.");
        printf("\n\n\n");
        printf("Do you want to view base information?\n");
        printf("1. Yes\n2. No\n");
        int option2;
        scanf("%d", &option2);
        if (option2 == 1)
        {
            printf("Enter your base ID to view: ");
            int base_id;
            scanf("%d", &base_id);
            viewexistingbase(base_id);
        }
        else if (option2 == 2)
        {
            printf("Exiting the program\n");
        }
        else
        {
            printf("Invalid option entered!\nExiting the program\n");
        }

        fclose(file);
    }
    else
    {
        // File does not exist
        printf("\nThe base with id %d does not exist.\n", base_id);
        printf("Exiting the program\n");
        sleep(5);
    }
}
int registernewbase()
{
    struct base b1;
    char rankoption;
    printf("\n\nRegistering New Base\n\n");

    printf("\nEnter your rank: ");
    printf("\n1. Colonel ---> C\n2. Lieutenant ---> L\n3. Major ---> M\n");
    scanf(" %c", &rankoption);

    if (rankoption == 'C' || rankoption == 'c')
    {
        strcpy(b1.rank, "Colonel");
    }
    else if (rankoption == 'L' || rankoption == 'l')
    {
        strcpy(b1.rank, "Lieutenant");
    }
    else if (rankoption == 'M' || rankoption == 'm')
    {
        strcpy(b1.rank, "Major");
    }
    else
    {
        printf("\nInvalid Option Entered!\nExiting The Program\n");
        return 0;
    }

    printf("\nYour rank is: %s (FOR TESTING PURPOSE ONLY)", b1.rank);
    printf("\nEnter your name: ");
    fflush(stdin);
    gets(b1.officialname);
    printf("\nEnter the location of your base: ");
    fflush(stdin);
    gets(b1.baselocation);
    printf("\nEnter the base duration(in minutes): ");
    if (scanf("%d", &b1.baseduration) != 1)
    {
        printf("\nInvalid Base Duration Entered!\n\n");
        return 0;
    }
    printf("\nEnter the strength of your base: ");
    if (scanf("%d", &b1.base_strength) != 1)
    {
        printf("\nInvalid Base Strength Entered!\n\n");
        return 0;
    }
    printf("\nEnter the destination of your base: ");
    scanf("%s", b1.destination);
    printf("\nYour base has been registered.");

    // ... (provisions calculation and output)
    // It will then give the output accordingly, such as the amount of weaponry, vehicles, food etc. required for the camp.
    int provisions[3] = {0, 0, 0};
    // provisions[0] = weapons
    // provisions[1] = vehicles
    // provisions[2] = food

    if (b1.base_strength <= 100)
    {
        provisions[0] = 10;
        provisions[1] = 5;
        provisions[2] = 10;
    }
    else if (b1.base_strength > 100 && b1.base_strength <= 200)
    {
        provisions[0] = 20;
        provisions[1] = 10;
        provisions[2] = 20;
    }
    else if (b1.base_strength > 200 && b1.base_strength <= 300)
    {
        provisions[0] = 30;
        provisions[1] = 15;
        provisions[2] = 30;
    }
    else if (b1.base_strength > 300 && b1.base_strength <= 400)
    {
        provisions[0] = 40;
        provisions[1] = 20;
        provisions[2] = 40;
    }
    else if (b1.base_strength > 400 && b1.base_strength <= 500)
    {
        provisions[0] = 50;
        provisions[1] = 25;
        provisions[2] = 50;
    }
    else if (b1.base_strength > 500 && b1.base_strength <= 600)
    {
        provisions[0] = 60;
        provisions[1] = 30;
        provisions[2] = 60;
    }
    else if (b1.base_strength > 600 && b1.base_strength <= 700)
    {
        provisions[0] = 70;
        provisions[1] = 35;
        provisions[2] = 70;
    }
    else if (b1.base_strength > 700 && b1.base_strength <= 800)
    {
        provisions[0] = 80;
        provisions[1] = 40;
        provisions[2] = 80;
    }
    else if (b1.base_strength > 800 && b1.base_strength <= 900)
    {
        provisions[0] = 90;
        provisions[1] = 45;
        provisions[2] = 90;
    }
    else if (b1.base_strength > 900 && b1.base_strength <= 1000)
    {
        provisions[0] = 100;
        provisions[1] = 50;
        provisions[2] = 100;
    }
    else if (b1.base_strength > 1000 && b1.base_strength <= 1100)
    {
        provisions[0] = 110;
        provisions[1] = 55;
        provisions[2] = 110;
    }
    else if (b1.base_strength > 1100 && b1.base_strength <= 1200)
    {
        provisions[0] = 120;
        provisions[1] = 60;
        provisions[2] = 120;
    }
    else if (b1.base_strength > 1200 && b1.base_strength <= 1300)
    {
        provisions[0] = 130;
        provisions[1] = 65;
        provisions[2] = 130;
    }
    else if (b1.base_strength > 1300 && b1.base_strength <= 1400)
    {
        provisions[0] = 140;
        provisions[1] = 70;
        provisions[2] = 140;
    }
    else if (b1.base_strength > 1400 && b1.base_strength <= 1500)
    {
        provisions[0] = 150;
        provisions[1] = 75;
        provisions[2] = 150;
    }
    else if (b1.base_strength > 1500 && b1.base_strength <= 1600)
    {
        provisions[0] = 160;
        provisions[1] = 80;
        provisions[2] = 160;
    }
    else if (b1.base_strength > 1600 && b1.base_strength <= 1700)
    {
        provisions[0] = 170;
        provisions[1] = 85;
        provisions[2] = 170;
    }
    else if (b1.base_strength > 1700 && b1.base_strength <= 1800)
    {
        provisions[0] = 180;
        provisions[1] = 90;
        provisions[2] = 180;
    }
    else if (b1.base_strength > 1800 && b1.base_strength <= 1900)
    {
        provisions[0] = 190;
        provisions[1] = 95;
        provisions[2] = 190;
    }
    else if (b1.base_strength > 1900 && b1.base_strength <= 2000)
    {
        provisions[0] = 200;
        provisions[1] = 100;
        provisions[2] = 200;
    }
    else
    {
        provisions[0] = 210;
        provisions[1] = 105;
        provisions[2] = 210;
    }

    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            printf("\nWeapons required: %d", provisions[i]);
        }
        else if (i == 1)
        {
            printf("\nVehicles required: %d", provisions[i]);
        }
        else if (i == 2)
        {
            printf("\nFood required: %d ration bags", provisions[i]);
        }
    }
    // It will also give a designated ID for that base.
    //  Working on this part

    srand(time(NULL));
    int baseID = rand() % 1000;
    printf("\nYour base ID is: %d", baseID);
    // Saving into file
    savingbaseinfotofile(b1, baseID);
    return 0;
}
int viewexistingbase(int baseID)
{
    printf("Viewing Existing Base\n");
    char filename[20];
    sprintf(filename, "Base_Ops_Pro_Base_Info_%d.txt", baseID);
    FILE *file;
    printf("Opening file %s FOR TESTING ONLY\n", filename);

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        printf("Base with such ID does not exit!\n");
        sleep(5);
        return 0;
    }
    char c;
    printf("\n\n\nThe base information is:\n");

    while ((c = getc(file)) != EOF)
    {
        printf("%c", c);
    }
    sleep(5);
    fclose(file);
    printf("\n\n\n");
    printf("Do you want to update base information?\n");
    printf("1. Yes\n2. No\n");
    int option;
    scanf("%d", &option);
    if (option == 1)
    {
        printf("Enter your base ID to update: ");
        int base_id;
        scanf("%d", &base_id);
        updatenewbase(base_id);
    }
    else if (option == 2)
    {
        printf("Exiting the program\n");
    }
    else
    {
        printf("Invalid option entered!\nExiting the program\n");
    }
    return 0;
}
void encryptor(FILE *fptr)
{	
	char c, ch;
	fptr = fopen("thebestfile.txt", "r+");
	if(fptr == NULL)
	{
		printf("error occoured...");
		exit(1);
	}
	fseek(fptr, 0, SEEK_SET);
	ch = fgetc(fptr);
	while(ch != EOF)
	{
		fseek(fptr, -1, SEEK_CUR);
		fprintf(fptr, "%c", ch + 45);
		fseek(fptr, 0, SEEK_CUR);
		ch = fgetc(fptr);
	}
	fclose(fptr);
	printf("\nFile has been encrypted...");
	
	printf("do you want to apply decryption? (y/n): ");
	scanf(" %c", &c);
	if(c == 'y')
	{
		decryptor(fptr);
	}
}

void decryptor (FILE *fptr)
{
	char ch;
	fptr = fopen("thebestfile.txt", "r+");
	if(fptr == NULL)
	{
		printf("error occoured...");
		exit(1);
	}
	fseek(fptr, 0, SEEK_SET);
	ch = fgetc(fptr);
	while(ch != EOF)
	{
		fseek(fptr, -1, SEEK_CUR);
		fprintf(fptr, "%c", ch - 45);
		fseek(fptr, 0, SEEK_CUR);
		ch = fgetc(fptr);
	}
	fclose(fptr);
	printf("\nFile has been decrypted...");
}
