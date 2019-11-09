#include <irrKlang.h>
#include <thread>
#include <Windows.h>
#include <string>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;
using namespace irrklang;

enum game_status
{
	Init,
	Start,
	PAUSE,
	STOP,
	GameOver,
	End
};

void Record(int *status);