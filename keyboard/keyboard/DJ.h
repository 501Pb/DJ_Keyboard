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
#define SPEED 500 // 단어가 생성되는 간격 (단위 : ms). 500이하는 플레이 어려움. ns
#define ONE_SECOND 1000 //1초에 해당하는 1000ms = 1s 

/*콘솔 글자 색상*/
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

#pragma comment(lib, "winmm.lib") //wav 파일 재생

//#define SOUND_FILE_NAME "../sound/do.wav"
//#define SOUND_FILE_NAME "..\\sound\\do.wav"

using namespace std;

void title(void);
void game_init(void);
bool game_over(void);
void play_game(void);
void InitData(void);
void display(void);

void random_word(void); //출력될 단어 랜덤으로 설정하는 함수
void help_function(); // 도움말 출력 함수
bool menu_function(); //메뉴 출력 함수
void GotoXY(int x, int y); //커서 이동 함수
void textcolor(int foreground, int background); //글자 색상 출력 함수

/*입력 스레드 함수*/
void* t_function(void* data); // 스레드화 할 사용자 입력 함수
void start_thread(); // 스레드 시작 함수
void end_thread(); // 스레드 중지 함수