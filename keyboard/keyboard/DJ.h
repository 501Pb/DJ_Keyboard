#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 3
#define MAP_X 74
#define MAP_Y 19
#define WORD_NUM 4

#define HAVE_STRUCT_TIMESPEC //thread 'timespec' 에러 방지 
#include "word.h"
#include <iostream>
#include <fstream>
#include <stdlib.h> //system()
#include <string>
#include <vector>
#include <windows.h>//sleep()
#include <conio.h>//getch() - 키입력
#include <cstdlib> //random
#include <ctime> //random
#include <mmsystem.h> //sound
#include <cstring>
#include <pthread.h> //thread() 
#define HAVE_STRUCT_TIMESPEC // windows.h와 pthread.h간의 시간 
#define SPEED 1000 // 단어가 생성되는 간격 (단위 : ms). 조절하여 난이도 증감 가능. 500이하는 플레이 어려움. ns
#define ONE_SECOND 1000 //1초에 해당하는 1000ms = 1s 
#pragma comment(lib, "winmm.lib") //wav 파일 재생

//#define SOUND_FILE_NAME "../sound/do.wav"
//#define SOUND_FILE_NAME "..\\sound\\do.wav"

using namespace std;

void title(void);
void game_init(void);
int game_over(void);
void play_game(void);
void InitData(void);
void display(void);
void Random_word(int i);

void help_function(); // 도움말 출력 함수
int menu_function(); //메뉴 출력 함수
void GotoXY(int x, int y); //커서 이동 함수
void DrawWord(int i);
