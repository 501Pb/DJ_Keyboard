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
#define SPEED 1000 // �ܾ �����Ǵ� ���� (���� : ms). �����Ͽ� ���̵� ���� ����. 500���ϴ� �÷��� �����. ns
#define ONE_SECOND 1000 //1�ʿ� �ش��ϴ� 1000ms = 1s 
#pragma comment(lib, "winmm.lib") //wav ���� ���

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

void help_function(); // ���� ��� �Լ�
int menu_function(); //�޴� ��� �Լ�
void GotoXY(int x, int y); //Ŀ�� �̵� �Լ�
void DrawWord(int i);
