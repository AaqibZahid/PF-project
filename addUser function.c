#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define USERNUM 3

typedef struct users {
	char fname[50];
	char lname[50];
	char rank[50];
	char password[50];
}users;

void saveDetails(users user[], int i, FILE *fptr)
{
	fprintf(fptr, "%s\n", user[i].fname);
	fprintf(fptr, "%s\n", user[i].lname);
	fprintf(fptr, "%s\n", user[i].rank);
	fprintf(fptr, "%s\n\n", user[i].password);
}

int adduser ()
{
	int totalUsers, i;
	while(totalUsers>USERNUM)
	{
		printf("enter number of users to add: ");
		scanf("%d", &totalUsers);
		if(totalUsers > USERNUM)
		{
			printf("Cannot exceed more than %d active users\n\n", USERNUM);
		}
	}
	
	FILE *fptr;
	fptr = fopen("usersinfo.txt", "a");
	users user[totalUsers];
	
	for(i=0; i<totalUsers; i++)
	{
		printf("\nenter details of user no.%d\n\n", i+1);
		printf("first name: ");
		scanf("%s", &user[i].fname);
		printf("last name: ");
		scanf("%s", &user[i].lname);
		printf("rank (colonel/lieutenant/brigadier): ");
		scanf("%s", &user[i].rank);
		printf("enter designated user password: ");
		scanf("%s", &user[i].password);
		saveDetails(user, i, fptr);
	}
	fclose(fptr);
	printf("New users have been added to the system");
	return 0;
}




