#include <irrKlang.h>
#include <thread>
#include <Windows.h>

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

enum game_status
{
	Init,
	Start,
	PAUSE,
	STOP,
	End
};

void Record(int *status);