#include <SDL.h>

#include "TPMain.h"

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

using namespace std;

// Program entry point - SDL manages the actual WinMain entry point for us
int main(int argc, char *argv[])
{
	TPMain &TP = TPMain::getInstance();
	TP.init();
	TP.run();

    return 0;
}