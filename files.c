//files.c

#include <string.h>

#include "files.h"
#include "options.h"


int numLists = 0;

static FILE* inFile = NULL;
static FILE* outFile = NULL;


int readInFile()
{
	inFile = fopen(getFlagArg(INPUT_FILE), "r");
	
	if(inFile == NULL)
	{
		perror("logParse: Error: Invalid infile specified");
		return -1;
	}
	else
	{
		fseek(inFile, 0, SEEK_END);
		int size = ftell(inFile);
		if(size == 0)
		{
			printf("logParse: Error: Infile is an empty file\n");
			return -1;
		}

		rewind(inFile);
	}

	int currentInt = 0;

	if(fscanf(inFile, "%d\n", &currentInt) > 0)
	{
		numLists = currentInt;
		//printf("numLists = %d\n", numLists);
	}
	else
	{
		printf("logParse: Error: Could not read first value from infile\n");
	}

	char* line = NULL;
	int numInts = 0;
	size_t len = 0;
	ssize_t read;


	/*while((read = getline(&line, &len, inFile)) != EOF)
	{
		char*token = strtok(line, " ");
		while(token != NULL)
		{
			printf("%s\n", token);
			token = strtok(NULL, " ");
		}
	}*/

	int i;
	for(i = 0; i < numLists; ++i)
	{
		pid_t pid = fork();
		wait(NULL);
		
		printf("This is pid: %d\n", pid);
		//getline called by parent to move the file pointer
		getline(&line, &len, inFile);
		//This is the child 
		if(pid == 0)
		{
			printf("%s", line);
			printf("I am child and I run the alg\n");
			exit(0);
		}
	}
	printf("\n");

	return 0;
}
