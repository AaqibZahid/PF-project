#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int fileEncryptor ();
int main ()
{
	fileEncryptor();
	printf("Encryption has been applied");
	return 0;
}

int fileEncryptor ()
{
	FILE *file1, *file2;
	char buffer;
	file1 = fopen("inputFile.txt", "r");
	if(file1 == NULL)
	{
		printf("file doesn't exist..\n");
		exit(1);
	}
	
	file2 = fopen("outputFile.txt", "w");
	if(file2 == NULL)
	{
		printf("error creating the file...");
		exit(1);
	}
	
	buffer = fgetc(file1);
	while(buffer != EOF)
	{
		fprintf(file2, "%c", buffer+45);
		buffer = fgetc(file1);
	}
	fclose(file1);
	fclose(file2);
	return 0;
	
}
