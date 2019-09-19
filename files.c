//files.c

#include <string.h>

#include "files.h"
#include "options.h"


int numLists = 0;

static FILE* inFile = NULL;
static FILE* outFile = NULL;

pid_t pid = -1;

bool isSubsetSum(int set[], int n, int sum)
{
	bool subset[n + 1][sum + 1];

	int i;
	for(i = 0; i <= n; i++)
	{
		subset[i][0] = true;
	}
	
	for(i = 1; i <= sum; i++)
	{
		subset[0][i] = false;
	}

	int j;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= sum; j++)
		{
			if(j < set[i - 1])
			{
				subset[i][j] = subset[i - 1][j];
			}
			if(j >= set[i - 1])
			{
				subset[i][j] = subset[i - 1][j] ||
						subset[i - 1][j - set[i - 1]];
			}
		}
	}

	//PRINT TABLE
	/*for(i = 0; i <= n; i++)
	{
		for(j = 0; j <= sum; j++)
		{
			printf("%4d", subset[i][j]);
		}
		printf("\n");
	}*/
	
	//RECURSIVE WAY OF DOING IT
	/*
	if(sum == 0)
	{
		return 1;
	}
	if(n == 0 && sum != 0)
	{
		return 0;
	}

	if(set[n-1] > sum)
	{
		return isSubsetSum(set, n-1, sum);
	}

	return isSubsetSum(set, n-1, sum) ||
				isSubsetSum(set, n-1, sum-set[n-1]);
	*/
	
	return subset[n][sum];
}

void setupForIsSubsetSum(char* set)
{
	char* line = NULL;
	int numInts = 0;
	size_t len = 0;
	ssize_t read;

	char *firstWord, *remainder, *context, *contextTwo;
	char delimiter[] = " ";
	int inputLength = strlen(set);
	char *inputCopy = (char*) calloc(inputLength + 1, sizeof(char));
	strncpy(inputCopy, set, inputLength);
	
	firstWord = strtok_r (inputCopy, delimiter, &context);
	remainder = context;
	printf("%s\n", firstWord);
	printf("%s\n", context);

	int counter = 1;
	int sum;
	sum = atoi(firstWord);
	printf("SUM IS: %d\n", sum);
		
		//Obtain number of words in the string
		int i;
		for(i = 0; context[i] != '\0'; i++)
		{
			if(context[i] == ' ' && context[i+1] != ' ')
			counter++;
		}

		int iterator = 0;
		int array[counter];
		char*token = strtok(context, " ");
		while(token != NULL)
		{
			printf("%s\n", token);
			array[iterator] = atoi(token);
			iterator++;
			token = strtok(NULL, " ");
		}

		//Ready for isSubsetSum function
		//bool flag = 0;
		//flag = isSubsetSum(array, counter, sum);
		if(isSubsetSum(array, counter, sum) == true)
		{
			printf("Found a subset with given sum\n");
		}
		else
		{
			printf("No subset with given sum\n");
		}
		/*int flag = 0;
		flag = isSubsetSum(array, counter, sum);
		printf("HERE IS THE FLAG: -----------------------> %d\n\n", flag);
		*/
		
		//PRINT ARRAY
		for(i = 0; i < counter; ++i)
		{
			printf("ARRAY: %d\n", array[i]);
		}
		
	free(inputCopy);
	for(i = 0; i < 12000; ++i)
	{
		printf("ope\n");
	}
	for(i = 0; i < 12000; ++i)
	{
		printf("ope\n");
	}
	for(i = 0; i < 12000; ++i)
	{
		printf("ope\n");
	}
	for(i = 0; i < 12000; ++i)
	{
		printf("ope\n");
	}
	printf("THE END\n");
}

void kill_child(int sig)
{
	kill(pid,SIGKILL);
}

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
		signal(SIGALRM,(void (*)(int))kill_child);
		pid = fork();
		/*pid_t pid = fork();
		wait(NULL);*/
		if(pid > 0)
		{
			alarm(1);

			wait(NULL);
			getline(&line, &len, inFile);
			
		}
		//printf("This is pid: %d\n", pid);
		//getline called by parent to move the file pointer
		/*getline(&line, &len, inFile);*/
		//This is the child 
		else if(pid == 0)
		{
			getline(&line, &len, inFile);
			setupForIsSubsetSum(line);
			//printf("%s", line);
			//printf("I am child and I run the alg\n");
			exit(0);
		}
	}
	printf("\n");

	return 0;
}
