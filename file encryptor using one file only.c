#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void encryptor (FILE *fptr);
void decryptor (FILE *fptr);

int main ()
{	
	FILE *fptr = NULL;
	encryptor(fptr);
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