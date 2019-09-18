#include "options.h"
#include "files.h"

int main(int argc, char** argv)
{
	setFlags(argc, argv);
	
	if(getFlagState(HELP) == 1)
	{
		printf("HELP\n");
		return 0;
	}

	readInFile();


	return 0;
}
