#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 3
#define MAP_X 74
#define MAP_Y 19
#define WORD_NUM 4
#include "word.h"
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <windows.h>//sleep()
#include <conio.h>//getch() - 키입력
#include <cstdlib> //random
#include <ctime> //random
#include <mmsystem.h> //sound

#pragma comment(lib, "winmm.lib") //wav 파일 재생

//#define SOUND_FILE_NAME "../sound/do.wav"
//#define SOUND_FILE_NAME "..\\sound\\do.wav"

using namespace std;

void title(void);
void game_init(void);
bool game_over(void);
void play_game(void);
void InitData(void);
void make_random(void);
void display(void);

string make_string(Word wd);
void make_word(void);
string print_space(int a);