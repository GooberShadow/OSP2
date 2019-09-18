
struct IntegerListQueue
{
	int _numLists;
	int* listSizes;
	int** intLists;
};

static struct IntegerListQueue* listsFromInFile;
