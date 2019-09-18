//options.h

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FLAGS 4

enum FLAG_LABELS
{
	HELP,
	INPUT_FILE,
	OUTPUT_FILE,
	TIME
};

void setFlags(const int argc, char** argv);

int getFlagState(int flag);
char* getFlagArg(int flag);

#endif
