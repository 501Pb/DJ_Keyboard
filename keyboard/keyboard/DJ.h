#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 3
#include <iostream>
#include <string>
#include <windows.h>//sleep()
#include <conio.h>//getch() - Ű�Է�
#include <conio.h>//getch() - Ű�Է�
#include <cstdlib> //random
#include <ctime> //random
#include <mmsystem.h> //sound
#include "word.h"

#pragma comment(lib, "winmm.lib") //wav ���� ���

//#define SOUND_FILE_NAME "../sound/do.wav"
//#define SOUND_FILE_NAME "..\\sound\\do.wav"

using namespace std;

void title(void);
void game_init(void);
bool game_over(void);
void play_game(void);