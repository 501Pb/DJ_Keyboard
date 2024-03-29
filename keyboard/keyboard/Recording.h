#ifndef __RECORDING__H__
#define __RECORDING__H__

#include <irrKlang.h>
#include <thread>
#include <Windows.h>
#include <string>
#include <iostream>
#include <io.h>
#include <direct.h>

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma warning(disable:4996)
#define SLEEPTIME 200

using namespace std;
using namespace irrklang;

enum class game_status
{
	Init,
	Start,
	PAUSE,
	GameOver,
	End
};

void Record(game_status*, string*);
#endif