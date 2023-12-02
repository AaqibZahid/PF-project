#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define USERNUM 3

typedef struct users {
	char fname[50];
	char lname[50];
	char rank[50];
	char password[50];
}users;

void addUsers();
void saveDetails(users user[], int i, FILE *fptr);
void passwordGenerator(char *password);

int main ()
{
	addUsers();
	return 0;
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
		
		printf("the password for official %s %s is: %s", user[i].fname, user[i].lname, user[i].password);
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

}

void saveDetails(users user[], int i, FILE *fptr)
{
	fprintf(fptr, "%s\n", user[i].fname);
	fprintf(fptr, "%s\n", user[i].lname);
	fprintf(fptr, "%s\n", user[i].rank);
	fprintf(fptr, "%s\n\n", user[i].password);
}
