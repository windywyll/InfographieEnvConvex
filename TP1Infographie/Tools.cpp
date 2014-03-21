// loadFile - loads text file into char* fname
// allocates memory - so need to delete after use

#include "Tools.h"

using namespace std;

char* loadFile(char *fname)
{
	int size;
	char * memblock;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	ifstream file (fname, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		size = (int) file.tellg(); // get file size
		memblock = new char [size+1]; // create buffer w space for null char
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();
		memblock[size] = 0;
		cout << "file " << fname << " loaded" << endl;
	}
	else
	{
		cout << "Unable to open file " << fname << endl;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
	}
	return memblock;
}

void exitFatalError(char *message)
{
    cout << message << " " << endl;
    cout << SDL_GetError();
    SDL_Quit();
    exit(1);
}