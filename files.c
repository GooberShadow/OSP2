//files.c

#include <string.h>

#include "files.h"
#include "options.h"

#define TIME_LIMIT 1

void alarm_handler(int);
void child_handler(int);

void listenForAlarm(int signal)
{
	printf("No valid subset found after 1 second ");
	exit(0);
}

int timeout = 0;
int child_done = 0;

int numLists = 0;

static FILE* inFile = NULL;
static FILE* outFile = NULL;

pid_t pid = -1;

void displaySubset(int subSet[], int size, int pidNum)
{
	int i;
	//printf("%d: ", pidNum);
	for(i = 0; i < size; i++)
	{
		printf("%d ", subSet[i]);
	}
	//printf("\n");
}

void subsetSum(int set[], int *subSet, int n, int subSize, int total, int nodeCount, int sum, int pidNum)
{
	if(total == sum)
	{
		printf(": ");
		displaySubset(subSet, subSize, pidNum);
		subsetSum(set,subSet,n,subSize-1,total-set[nodeCount],nodeCount+1,sum, pidNum);
		return;
	}
	else
	{
		int i;
		subSet = (int*) realloc(subSet, n * sizeof(int));
		for(i = nodeCount; i < n; i++)
		{
			subSet[subSize] = set[i];
			subsetSum(set,subSet,n,subSize+1,total+set[i],i+1,sum, pidNum);
		}
	}
}

void findSubset(int set[], int size, int sum, int pidNum)
{
	//int b=100;
	int *subSet = NULL;
	//int *subSet = (int*) malloc(b * sizeof(int));
	subsetSum(set, subSet, size, 0, 0, 0, sum, pidNum);

	free(subSet);
}

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

void setupForIsSubsetSum(char* set, int pidNum)
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
	//printf("%s\n", firstWord);
	//printf("%s\n", context);

	int counter = 1;
	int sum;
	sum = atoi(firstWord);
	//printf("SUM IS: %d\n", sum);
		
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
			//printf("%s\n", token);
			array[iterator] = atoi(token);
			iterator++;
			token = strtok(NULL, " ");
		}


		
		//Ready for isSubsetSum function
		//bool flag = 0;
		//flag = isSubsetSum(array, counter, sum);
		
		if(isSubsetSum(array, counter, sum))
		{
			findSubset(array, counter, sum, pidNum);
		}
		else
		{
			printf("No subset of numbers summed to %d ", sum);
		}

		//ORIGINAL IDEA
		/*if(isSubsetSum(array, counter, sum) == true)
		{
			printf("Found a subset with given sum\n");
		}
		else
		{
			printf("No subset with given sum\n");
		}*/


		/*int flag = 0;
		flag = isSubsetSum(array, counter, sum);
		printf("HERE IS THE FLAG: -----------------------> %d\n\n", flag);
		*/
		
		//PRINT ARRAY
		/*for(i = 0; i < counter; ++i)
		{
			printf("ARRAY: %d\n", array[i]);
		}*/
		
	free(inputCopy);
	//TESTING FOR LOOPS FOR TIMEOUT
	/*for(i = 0; i < 12000; ++i)
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
	for(i = 0; i < 12000; ++i)
	{
		printf("ope\n");
	}
	printf("THE END\n");
	*/
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
	int pidNum;
	for(i = 0; i < numLists; ++i)
	{
		
		getline(&line, &len, inFile);
		//signal(SIGALRM,(void (*)(int))kill_child);
		//pid = fork();
		pid_t pid = fork();
		if(pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}

		if(pid > 0)
		{
			pidNum = pid;
			//printf("%d: ", pid);
		}
		/*if(pid > 0)
		{
			alarm(1);

			wait(NULL);
			getline(&line, &len, inFile);
			
		}*/
		//printf("This is pid: %d\n", pid);
		//getline called by parent to move the file pointer
		//This is the child 
		else if(pid == 0)
		{
			//CHILD Process
			//TESTING FOR ALARM BELOW
			alarm(1);
			signal(SIGALRM, listenForAlarm);
			
			//getline(&line, &len, inFile);
			setupForIsSubsetSum(line, pidNum);
			//printf("%s", line);
			//printf("I am child and I run the alg\n");
			exit(0);
		}

		//ALARM FROM ONLINE THING
		/*signal(SIGALRM, alarm_handler);
		signal(SIGCHLD, child_handler);

		alarm(TIME_LIMIT);
		pause();
		if(timeout)
		{
			printf("Alarm Triggered\n");
			int result = waitpid(pid, NULL, WNOHANG);
			if(result == 0)
			{
				//Child is still running so end it
				printf("killing child\n");
				kill(pid, SIGKILL);
				wait(NULL);
			}
			else
			{
				printf("alarm triggered but child finished normally\n");
			}
		}
		else if(child_done)
		{
			printf("child finished normally\n");
			wait(NULL);
		}*/

		//BEFORE CHANGES
		wait(NULL);
		if(pid > 0)
		{	
			//printf("Parent ID: %d", getpid());
			//pidNum = pid;
			printf(" ::via pid:: %d \n", pid);
		}
	}
	printf("\n");

	return 0;
}

void child_handler(int sig)
{
	child_done = 1;
}

void alarm_handler(int sig)
{
	timeout = 1;
}
