#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

char allPasswords[4][7] = {{0}};
char password[7] = "abc123";
strcpy(allPasswords[0], password);
int passwordCopyCnt = 0;
	
typedef struct users {
	char fname[50];
	char lname[50];
	char rank[50];
	char password[50];
}users;

void addUsers();
void saveDetails(users user[], int i, FILE *fptr);
void passwordGenerator(char *password);
int menuWithAddUser();
int menuWithoutAddUser();

int main() 
{
	int exitProgram = 0, option;
    int isPasswordCorrect = 0, *isPaswordCorrectPtr = &isPasswordCorrect;
    //int userPassword;
    int attempt,i;
    int baseIDToUpdate;
    int baseIDToView;
    char isMajor;
	password();

    while (!exitProgram)
	{
    	//password input and verification
    	password();
        
        if (*isPasswordCorrectPtr)
		{
			printf("are you of rank major or not: ");
			scanf(" %c", &isMajor);
		}
		if(isMajor == 'y' || 'Y')
		{
			menuWithAddUser();
			break;
		}
		else
		{
			menuWithoutAddUser();
			break;
		}
	}
	return 0;
}


int menuWithAddUser(*option)
{
	printf("Welcome Major. Select options: \n");
	printf("\nOptions:");
    printf("\n1. Register New Base or Update existing base or View existing base ");
    printf("\n2. Update Existing Base");
    printf("\n3. View Existing Base");
    printf("\n4. Encrypt Base Information");
    printf("\n5. Add Vehicles");
    printf("\n6. Check Vehicle by ID");
    printf("\n7. Give War Alert");
    printf("\n8. Other Options");
    printf("\n9. Add users");
    printf("\n10. Exit Program");
    printf("\nEnter your choice: ");
    scanf("%d", &option);
        //add here the witch case options
    return option;
}

int menuWithoutAddUser()
{
	printf("Welcome Major. Select options: \n");
	printf("\nOptions:");
    printf("\n1. Register New Base or Update existing base or View existing base ");
    printf("\n2. Update Existing Base");
    printf("\n3. View Existing Base");
    printf("\n4. Encrypt Base Information");
    printf("\n5. Add Vehicles");
    printf("\n6. Check Vehicle by ID");
    printf("\n7. Give War Alert");
    printf("\n8. Other Options");
    printf("\n9. Exit Program");
    printf("\nEnter your choice: ");
    scanf("%d", &option);
     //add here the swtich case options
    return option;
}


//changed the password 54321 to abc123 string so that all passwords are of same type
//made array of allPasswords[4][7] which contains userPassword = abc123, and remaibning 3 user passwords
void password ()
{
	int cnt = 0, i;
	char userpassword[7];
	
	printf("Welcome to BaseOps Pro!\nEnter the password: ");
	scanf("%s", userpassword);
	
	for(i=0; i<4 && allPasswords[i] != '\0'; i++)
	{
		if(strcmp(userpassword, allPasswords[i]) == 0)
		{
			printf("Correct! Welcome...");
			*isPasswordCorrectPtr = 1;
			break;
		}
	}
	if(*isPasswordCorrectPtr != 1)
	{
		for(i=1; i<=3; i++)
		{
			if(i == 1 || i == 2)
			{
				printf("\nYou have entered wrong password!\nTry Again.... (%d tries left)\n", 3-i);
			}
			
			else if(i == 3)
			{
				printf("\nUnauthorized Access Alert!!!\nSystem Criticality Compromised!!!");
				return 0;
			}
		}
	}
}



void addUsers()
{
	//declarations
	int totalUsers, i;
	char rankch;
	FILE *fptr = NULL;
	
	fptr = fopen("addedUsersInfo.txt", "a");
	if(fptr == NULL)
	{
		printf("\nError accessing the file\n");
		exit(1);
	}
	
	//taking no. of users less than USERNUM to add
	do
	{
		printf("enter number of users not more than %d: ", USERNUM);
		scanf("%d", &totalUsers);
		if(totalUsers > USERNUM)
		{
			printf("Cannot exceed more than %d active users\n\n", USERNUM);
		}
		else
		{
			printf("configuring settings for adding %d users: ", totalUsers);
		}
	}while(totalUsers>USERNUM);
	
	users user[totalUsers];
	
	//reading details (first,last name, rank, and generating alphanumeric password) of the users
	for(i=0; i<totalUsers; i++)
	{
		printf("\nenter details of user no.%d\n\n", i+1);
		printf("first name: ");
		scanf("%s", &user[i].fname);
		while(getchar() != '\n');
		printf("last name: ");
		scanf("%s", &user[i].lname);
		while(getchar() != '\n');
		
		while(1)
		{
			//reading rank ( change rank if required )
			fflush(stdin);
			printf("enter rank ( colonel(c) - lieutenant(l) - brigadier(b) ): ");
			rankch = getchar();
			
			if(rankch == 'c' || rankch == 'C')
			{
				strcpy(user[i].rank, "colonel");
				break;
			}
			else if(rankch == 'l' || rankch == 'L')
			{
				strcpy(user[i].rank, "lieutenant");
				break;
			}
			else if(rankch == 'b' || rankch == 'B')
			{
				strcpy(user[i].rank, "brigadier");
				break;
			}
			else
			{
				printf("incorrect rank entered..Enter again:\n");
			}
		}
		while(getchar() != '\n');
		
		//generating password
		passwordGenerator(user[i].password);
		
		printf("the password for official %s %s is: %s\n", user[i].fname, user[i].lname, user[i].password);
		saveDetails(user, i, fptr);
	}
	
	fclose(fptr);
	printf("New users have been added to the system\n");
}

void passwordGenerator(char *password)
{
	int i, k, randPos;
	char numericPart[] = "0123456789", alphabeticPart[] = "abcdefghijklmnopqrstuvwxyz";
	
	srand(time(0));
	
	for(i=0, k=0; i<3; i++, k++)
	{
		randPos = rand() % (strlen(alphabeticPart));
		password[k] = alphabeticPart[randPos];
	}                      
	for(i=0; i<3; i++,k++)
	{
		randPos = rand() % (strlen(numericPart));
		password[k] = numericPart[randPos];
	}
	
	password[6] = '\0';
	
	passwordCopyCnt++;
	
	strcpy(allPasswords[passwordCopyCnt - 1], password);

}

void saveDetails(users user[], int i, FILE *fptr)
{
	fprintf(fptr, "%s\n", user[i].fname);
	fprintf(fptr, "%s\n", user[i].lname);
	fprintf(fptr, "%s\n", user[i].rank);
	fprintf(fptr, "%s\n\n", user[i].password);
}
