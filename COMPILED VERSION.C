#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
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
