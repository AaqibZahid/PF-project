// DEFINING LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <unistd.h>
#include <ctype.h>
#define USERNUM 100
// DEFINING STRUCTURES
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
typedef struct users
{
    char fname[50];
    char lname[50];
    char rank[50];
    char password[50];
} users;
struct base
{
    char rank[50], officialname[50], baselocation[50], destination[50];
    int baseduration, base_strength;
};
struct Vehicle
{
    int id;
    int car_id;
    char name[20];
};
struct army
{
    int tanks;
    int planes;
    int soldiers;
};
struct Asset
{
    int id;
    char name[50];
    float value;
};
// FUNCTIONS PROTOTYPE
void password(int j);
void provideTasks(struct Soldier soldier);
int validateRank(int rank);
void addUsers();
void saveDetails(users user[], int i, FILE *fptr);
void passwordGenerator(char *password);
void savingbaseinfotofile(struct base b1, int baseID);
int updatenewbase(int base_id);
int registernewbase();
int viewexistingbase(int baseID);
void encryptor(FILE *fptr);
void decryptor(FILE *fptr);
void addVehicle(FILE *fptr);
void checkVehicleByID(FILE *fptr);
int ruv();
void beep();
void addAsset();
void checkAssetHistory(FILE *fptr);
void provideTasks(struct Soldier soldier);
int validateRank(int rank);
// FUNCTIONS DEFINITION
void password(int j)
{
    FILE *fptr = fopen("addedUsersInfo.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    char password1[] = "54321", password2[] = "12345", password3[] = "80808", userpassword[8], filepass[8];
    int i, k;

    printf("Welcome to BaseOps Pro!\nEnter the password: ");
    scanf("%s", userpassword);

    i = 0;
    while (i < 3)
    {
        k = 0;
        while (k < 4 && fscanf(fptr, "%s", filepass) == 1)
        {
            if (strcmp(userpassword, filepass) == 0 || strcmp(userpassword, password1) == 0 || strcmp(userpassword, password2) == 0 || strcmp(userpassword, password3) == 0)
            {
                printf("Correct! Welcome...\n");
                fclose(fptr);
                return;
            }
            k++;
        }

        i++;
        if (i == 3)
        {
            j++;
            if (j <= 3)
            {
                printf("\nWrong username or password\nTry Again: \n");
                fclose(fptr);
                password(j);
            }
            else
            {
                printf("\n3 Wrong tries\nPlease try again later\n");
                fclose(fptr);
                exit(0);
            }
        }
    }

    fclose(fptr);
}
void addUsers()
{
    // declarations
    int totalUsers, i;
    char rankch;
    FILE *fptr = NULL;

    fptr = fopen("addedUsersInfo.txt", "a");
    if (fptr == NULL)
    {
        printf("\nError accessing the file\n");
        exit(1);
    }

    // taking no. of users less than USERNUM to add
    do
    {
        printf("Enter number of users not more than %d: ", USERNUM);
        scanf("%d", &totalUsers);
        if (totalUsers > USERNUM)
        {
            printf("Cannot exceed more than %d active users\n\n", USERNUM);
        }
        else
        {
            printf("Configuring settings for adding %d users: ", totalUsers);
        }
    } while (totalUsers > USERNUM);

    users user[totalUsers];

    // reading details (first,last name, rank, and generating alphanumeric password) of the users
    for (i = 0; i < totalUsers; i++)
    {
        printf("\nEnter details of user no.%d\n\n", i + 1);
        printf("First name: ");
        scanf("%s", &user[i].fname);
        while (getchar() != '\n')
            ;
        printf("Last name: ");
        scanf("%s", &user[i].lname);
        while (getchar() != '\n')
            ;

        while (1)
        {
            // reading rank ( change rank if required )
            fflush(stdin);
            printf("Enter rank ( 1.Colonel(c) - 2.Lieutenant(l) - 3.Brigadier(b) ): ");
            rankch = getchar();

            if (rankch == 'c' || rankch == 'C')
            {
                strcpy(user[i].rank, "Colonel");
                break;
            }
            else if (rankch == 'l' || rankch == 'L')
            {
                strcpy(user[i].rank, "Lieutenant");
                break;
            }
            else if (rankch == 'b' || rankch == 'B')
            {
                strcpy(user[i].rank, "Brigadier");
                break;
            }
            else
            {
                printf("Incorrect rank entered..Enter again:\n");
            }
        }
        while (getchar() != '\n')
            ;

        // generating password
        passwordGenerator(user[i].password);

        printf("The password for official %s %s is: %s", user[i].fname, user[i].lname, user[i].password);
        saveDetails(user, i, fptr);
    }

    fclose(fptr);
    printf("\nNew users have been added to the system\n");
}

void passwordGenerator(char *password)
{
    int i, k, randPos;
    char numericPart[] = "0123456789", alphabeticPart[] = "abcdefghijklmnopqrstuvwxyz";

    srand(time(0));

    for (i = 0, k = 0; i < 3; i++, k++)
    {
        randPos = rand() % (strlen(alphabeticPart));
        password[k] = alphabeticPart[randPos];
    }
    for (i = 0; i < 3; i++, k++)
    {
        randPos = rand() % (strlen(numericPart));
        password[k] = numericPart[randPos];
    }
    password[6] = '\0';
}
void saveDetails(users user[], int i, FILE *fptr)
{
    fprintf(fptr, "%s\n", user[i].fname);
    fprintf(fptr, "%s\n", user[i].lname);
    fprintf(fptr, "%s\n", user[i].rank);
    fprintf(fptr, "%s\n\n", user[i].password);
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
int taskassigning()
{
    int i, j, numSoldiers;
    printf("Enter the number of soldiers: ");
    scanf("%d", &numSoldiers);
    for (i = 0; i < numSoldiers; i++)
    {
        struct Soldier recruit;
        printf("Enter recruit's name: ");
        scanf("%s", recruit.name);
        printf("Enter recruit's rank (4 for Lieutenant, 5 for Major, 6 for Colonel, etc.): ");
        scanf("%d", &recruit.rank);
        if (!validateRank(recruit.rank))
        {
            printf("Invalid rank for soldier %s! Exiting the program.\n", recruit.name);
            exit(1);
        }
        printf("Enter the number of tasks for %s: ", recruit.name);
        scanf("%d", &recruit.numTasks);
        recruit.tasks = (struct Task *)malloc(recruit.numTasks * sizeof(struct Task));
        for (j = 0; j < recruit.numTasks; j++)
        {
            printf("Enter task %d description: ", j + 1);
            scanf("%s", recruit.tasks[j].description);
            recruit.tasks[j].number = j + 1;
        }
        provideTasks(recruit);
        free(recruit.tasks);
    }
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
    int choice;
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
    printf("\nYour rank is: %s", b1.rank);
    printf("\nEnter your name: ");
    fflush(stdin);
    gets(b1.officialname);
    printf("\nEnter the location of your base: ");
    fflush(stdin);
    gets(b1.baselocation);
    printf("\nEnter the base duration (in minutes): ");
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
    int provisions[3] = {0, 0, 0};
    int i;
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
    for (i = 0; i < 3; i++)
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
    // Generating a designated ID for the base
    srand(time(NULL));
    int baseID = rand() % 1000;
    printf("\nYour base ID is: %d", baseID);
    // Saving into file
    savingbaseinfotofile(b1, baseID);
    // Adding assets or vehicles using switch cases
    do
    {
        printf("\n\nChoose an option:");
        printf("\n1. Add Assets");
        printf("\n2. Add Vehicles");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addassets();
            break;
        case 2:
            addvehicle();
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
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
void addAsset()
{
    FILE *fptr = fopen("assets.txt", "a+");
    if (fptr == NULL)
    {
        printf("Error opening file!");
        return;
    }
    struct Asset newAsset;
    printf("\nEnter asset ID: ");
    scanf("%d", &newAsset.id);
    printf("Enter asset name: ");
    scanf("%s", newAsset.name);
    printf("Enter asset value: ");
    scanf("%f", &newAsset.value);
    fprintf(fptr, "%d %s %.2f\n", newAsset.id, newAsset.name, newAsset.value);
    fflush(fptr);
    fclose(fptr);
    printf("Asset added successfully.\n");
}
void checkAssetHistory(FILE *fptr)
{
    int id;
    int searchId;
    char name[50];
    float value;
    int found = 0;

    printf("Enter asset ID to check history: ");
    scanf("%d", &searchId);

    rewind(fptr);
    while (fscanf(fptr, "%d %s %f", &id, name, &value) == 3)
    {
        if (searchId == id)
        {
            found = 1;
            printf("\nAsset ID matched!");
            printf("\n%d %s %.2f\n", id, name, value);
            break;
        }
    }

    if (!found)
    {
        printf("\nNo asset found with the given ID.\n");
    }
}
int assets()
{
    int choice;
    FILE *fptr = fopen("assets.txt", "a+");
    if (fptr == NULL)
    {
        printf("Error opening file!");
        return 1;
    }
    do
    {
        printf("\n1. Add a new asset");
        printf("\n2. Check asset history by ID");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addAsset();
            break;
        case 2:
            checkassetsbyid();
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    fclose(fptr);
    return 0;
}
int addassets()
{
    int choice;
    FILE *fptr = fopen("assets.txt", "a+");
    if (fptr == NULL)
    {
        printf("Error opening file!");
        return 1;
    }
    do
    {
        printf("\n1. Add a new asset");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addAsset();
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    fclose(fptr);
    return 0;
}
int checkassetsbyid()
{
    int choice;
    FILE *fptr = fopen("assets.txt", "a+");
    if (fptr == NULL)
    {
        printf("Error opening file!");
        return 1;
    }
    do
    {
        printf("\n1. Check asset history by ID");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            checkAssetHistory(fptr);
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    fclose(fptr);
    return 0;
}
int ruv()
{
    int option;
    printf("Welcome to Base Ops Pro!\n");
    printf("Do you want to Register, View or update the base?\n");
    printf("1. Register New Base\n2. Update Existing Base\n3. View Existing Base\n");
    int option1;
    scanf("%d", &option1);
    if (option1 == 1)
    {
        printf("Registering New Base\n");
        registernewbase();
        printf("\n\n");
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
        }
        else
        {
            printf("Invalid option entered!\nExiting the program\n");
        }
    }
    else if (option1 == 2)
    {
        printf("Updating Existing Base\n");
        printf("Enter your base ID to update: ");
        int base_id;
        scanf("%d", &base_id);
        updatenewbase(base_id);
    }
    else if (option1 == 3)
    {
        printf("Viewing Existing Base\n");
        printf("Choose Option:\n1. View Existing base\n2. Check Assets By Id\n3. Check Vehicles By Id\n4. Exit Program\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("Enter your base ID to view: ");
            int base_id;
            scanf("%d", &base_id);
            viewexistingbase(base_id);
            break;
        case 2:
            checkassetsbyid();
            break;
        case 3:
            checkvehiclebyid();
            break;
        case 4:
            return 0;
        default:
            ("Invalid Option Entered!");
        }
    }
    else
    {
        printf("Invalid option entered!\nExiting the program\n");
        sleep(5);
        return 0;
    }
    sleep(1);
    return 0;
}

void encryptor(FILE *fptr)
{
    char c, ch;
    fptr = fopen("baseopsproencryptor.txt", "w+");
    FILE *file2;
    file2 = fopen("assets.txt", "r");
    if (fptr == NULL)
    {
        printf("error occoured...");
        exit(1);
    }
    fseek(fptr, 0, SEEK_SET);
    ch = fgetc(fptr);
    while (ch != EOF)
    {
        fseek(fptr, -1, SEEK_CUR);
        fprintf(file2, "%c", ch + 45);
        fseek(fptr, 0, SEEK_CUR);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    printf("\nFile has been encrypted...");

    printf("do you want to apply decryption? (y/n): ");
    scanf(" %c", &c);
    if (c == 'y')
    {
        decryptor(fptr);
    }
}

void decryptor(FILE *fptr)
{
    char ch;
    fptr = fopen("assets.txt", "r+");
    if (fptr == NULL)
    {
        printf("error occoured...");
        exit(1);
    }
    fseek(fptr, 0, SEEK_SET);
    ch = fgetc(fptr);
    while (ch != EOF)
    {
        fseek(fptr, -1, SEEK_CUR);
        fprintf(fptr, "%c", ch - 45);
        fseek(fptr, 0, SEEK_CUR);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    printf("\nFile has been decrypted...");
}
void addVehicle(FILE *fptr)
{
    struct Vehicle newVehicle;

    printf("\nEnter ID No: ");
    scanf("%d", &newVehicle.id);

    printf("Enter vehicle name: ");
    scanf("%s", newVehicle.name);

    printf("Enter Vehicle Id: ");
    scanf("%d", &newVehicle.car_id);

    fprintf(fptr, "%s %d\n", newVehicle.name, newVehicle.car_id);
    printf("Vehicle added successfully.\n");
}

void checkVehicleByID(FILE *fptr)
{
    int id;
    char name[20];
    int car_id;

    printf("Enter ID to check: ");
    scanf("%d", &id);

    rewind(fptr);

    while (fscanf(fptr, "%s %d", name, &car_id) == 2)
    {
        if (id == car_id)
        {
            printf("\nID matched!");
            printf("\n%s %d\n", name, car_id);
            return;
        }
    }

    printf("\nNo vehicle found with the given ID.\n");
}
void beap()
{
    int count = 10;
repeat:
    Beep(1000, 500);
    count--;
    if (count > 0)
    {
        goto repeat;
    }
}
int war()
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
        int num = rand() % 50 + 1;
        int num1 = rand() % 50 + 1;
        int num2 = rand() % 300 + 1;
        // Winning condition
        int winning = rand() % 100 + 1;
        if (winning > 90)
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
int vehicle()
{
    int choice;
    FILE *fptr = fopen("vehicles.txt", "a+");

    if (fptr == NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    do
    {
        printf("\n1. Add a new vehicle");
        printf("\n2. Check a vehicle by ID");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addVehicle(fptr);
            break;
        case 2:
            checkVehicleByID(fptr);
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    fclose(fptr);
    return 0;
}
int addvehicle()
{
    int choice;
    FILE *fptr = fopen("vehicles.txt", "a+");

    if (fptr == NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    do
    {
        printf("\n1. Add a new vehicle");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addVehicle(fptr);
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    fclose(fptr);
    return 0;
}
int checkvehiclebyid()
{
    int choice;
    FILE *fptr = fopen("vehicles.txt", "a+");

    if (fptr == NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    do
    {
        printf("\n1. Check a vehicle by ID");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            checkVehicleByID(fptr);
            break;
        case 0:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    fclose(fptr);
    return 0;
}
int main()
{
    system("cls");
    FILE *fptr = NULL;
    int exitProgram = 0;
    int isPasswordCorrect = 0;
    int validPasswords[] = {54321, 12345, 80808};
    int userPassword;
    int attempt, i;
    int baseIDToUpdate;
    int baseIDToView;

    while (!exitProgram)
    {
        // Welcome message and password input
        printf("Welcome to BaseOps Pro!\nEnter the password: ");
        int attempt = 1;
        for (attempt = 1; attempt <= 3; attempt++)
        {
            scanf("%d", &userPassword);

            for (i = 0; i < sizeof(validPasswords) / sizeof(validPasswords[0]); i++)
            {
                if (userPassword == validPasswords[i])
                {
                    printf("Correct! Welcome...\n");
                    isPasswordCorrect = 1;
                    break;
                }
            }

            if (isPasswordCorrect)
            {
                break;
            }
            else
            {
                if (attempt < 3)
                {
                    printf("\nYou have entered the wrong password! Try again... (%d tries left)\n", 3 - attempt);
                }
                else
                {
                    printf("\nUnauthorized Access Alert!!! \nSystem Criticality Compromised!!!\n");
                    beap();
                    exit(1);
                }
            }
        }
        int option;
        printf("\nOptions:");
        printf("\n1. Register New Base or Update existing base or View existing base ");
        printf("\n2. Add Vehicles or Check Vehicles By id");
        printf("\n3. Add Assets or Check Assets By Id");
        printf("\n4. War Alert");
        printf("\n5. Assign Tasks");
        printf("\n6. Add User");
        printf("\n7. File Encrypt");
        printf("\n8. File Decrypt");
        printf("\n9. Exit Program");
        printf("\nEnter your choice: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            ruv();
            break;
        case 2:
            vehicle();
            break;
        case 3:
            assets();
            break;
        case 4:
            war();
            break;
        case 5:
            taskassigning();
            break;
        case 6:
            addUsers();
            break;
        case 7:
            encryptor(fptr);
            break;
        case 8:
            decryptor(fptr);
            break;
        case 9:
            printf("\nExiting the program!");
            return 0;
        default:
            printf("Invalid option! Please enter a valid option.\n");
            break;
        }
        return 0;
    }
}