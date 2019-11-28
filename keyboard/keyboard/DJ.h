#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUM 3
#define MAP_X 74
#define MAP_Y 19
#define WORD_NUM 4

#define HAVE_STRUCT_TIMESPEC //thread 'timespec' ���� ���� 
#include "word.h"
#include <iostream>
#include <fstream>
#include <stdlib.h> //system()
#include <string>
#include <vector>
#include <windows.h>//sleep()
#include <conio.h>//getch() - Ű�Է�
#include <cstdlib> //random
#include <ctime> //random
#include <mmsystem.h> //sound
#include <cstring>
#include <pthread.h> //thread() 
#define HAVE_STRUCT_TIMESPEC // windows.h�� pthread.h���� �ð� 
#define SPEED 500 // �ܾ �����Ǵ� ���� (���� : ms). 500���ϴ� �÷��� �����. ns
#define ONE_SECOND 1000 //1�ʿ� �ش��ϴ� 1000ms = 1s 

/*�ܼ� ���� ����*/
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

#pragma comment(lib, "winmm.lib") //wav ���� ���

//#define SOUND_FILE_NAME "../sound/do.wav"
//#define SOUND_FILE_NAME "..\\sound\\do.wav"

using namespace std;

void title(void);
void game_init(void);
bool game_over(void);
void play_game(void);
void InitData(void);
void display(void);

void random_word(void); //��µ� �ܾ� �������� �����ϴ� �Լ�
void help_function(); // ���� ��� �Լ�
bool menu_function(); //�޴� ��� �Լ�
void GotoXY(int x, int y); //Ŀ�� �̵� �Լ�
void textcolor(int foreground, int background); //���� ���� ��� �Լ�

/*�Է� ������ �Լ�*/
void* t_function(void* data); // ������ȭ �� ����� �Է� �Լ�
void start_thread(); // ������ ���� �Լ�
void end_thread(); // ������ ���� �Լ�