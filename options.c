//options.c

#include "options.h"

static int flagArray[NUM_FLAGS];

static void printFlagArray();

static char* inputFileParam = "input.dat";
static char* outputFileParam = "output.dat";
static int timeParam = 10;

static void initFlags()
{
	int i;
	for(i = 0; i < NUM_FLAGS; ++i)
	{
		flagArray[i] = 0;
	}
}

void setFlags(const int argc, char** argv)
{
	initFlags();

	int currentOption = -1;
	while((currentOption = getopt(argc, argv, "hi:o:t:")) != -1)
	{
		switch(currentOption)
		{
			case 'h':
				flagArray[HELP] = 1;
				break;
			case 'i':
				flagArray[INPUT_FILE] = 1;
				inputFileParam = optarg;
				break;
			case 'o':
				flagArray[OUTPUT_FILE] = 1;
				outputFileParam = optarg;
				break;
			case 't':
				flagArray[TIME] = 1;
				timeParam = atoi(optarg);
		}
	}
}

int getFlagState(int flag) 
{
	if(flag < NUM_FLAGS && flag >= 0)
	{	
		return flagArray[flag];
	}
	
	return -1;
}

char* getFlagArg(int flag)
{
	if(flag == HELP)
	{
		return "Help requires no argument";
	}
	if(flag == INPUT_FILE && inputFileParam != NULL)
	{
		return inputFileParam;
	}
	else if(flag == INPUT_FILE)
	{
		return "Input file not specified";
	}

	if(flag == OUTPUT_FILE && outputFileParam != NULL)
	{
		return outputFileParam;
	}
	else if(flag == OUTPUT_FILE)
	{
		return "Output file not specified";
	}

	if(flag == TIME)
	{
		char* timeString;
		sprintf(timeString, "%d", timeParam);
		return timeString;
	}

	return "Invalid flag value passed to function getFlagArg";
}

static void printFlagArray()
{
	int i;
	for(i = 0; i < NUM_FLAGS; ++i)
	{
		switch(i)
		{
			case HELP:
				printf("HelpFlag[%d] = %d\n", i, flagArray[i]);
				break;
			case INPUT_FILE:
				printf("InFlag[%d] = %d (%s)\n", i, flagArray[INPUT_FILE], inputFileParam);
				break;
			case OUTPUT_FILE:
				printf("OutFlag[%d] = %d (%s)\n", i, flagArray[OUTPUT_FILE], outputFileParam);
				break;
			case TIME:
				printf("TimeFlag[%d] = %d (%d)\n", i, flagArray[TIME], timeParam);
				break;

		}
	}
}
