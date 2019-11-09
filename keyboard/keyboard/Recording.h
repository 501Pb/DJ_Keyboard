#include <irrKlang.h>
#include <thread>
#include <Windows.h>

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;
using namespace irrklang;

enum game_status
{
	Init,
	Start,
	PAUSE,
	STOP,
	End
};

void Record(int *status);