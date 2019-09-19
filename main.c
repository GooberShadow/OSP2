#include "options.h"
#include "files.h"

void timeAlarm(int signal)
{
	printf("Time t has expired and the program is ending\n");
	exit(0);
}

int main(int argc, char** argv)
{
	setFlags(argc, argv);
	
	if(getFlagState(HELP) == 1)
	{
		printf("HELP\n");
		return 0;
	}
	if(getFlagState(TIME) == 1)
	{

	}
	else
	{
		alarm(10);
		signal(SIGALRM, timeAlarm);
		//TESTING IF IT WORKS
		//sleep(100);
	}

	readInFile();


	return 0;
}
