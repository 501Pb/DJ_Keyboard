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
#define SPEED 500 // �ܾ �����Ǵ� ���� (���� : ms). �����Ͽ� ���̵� ���� ����. 500���ϴ� �÷��� �����. ns
#define ONE_SECOND 1000 //1�ʿ� �ش��ϴ� 1000ms = 1s 

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

/*����� ������ �Լ�*/
void* t_function1(void* data); // ������ȭ �� ����� �Է� �Լ�
void start_thread1(); // ������ ���� �Լ�
void end_thread1(); // ������ ���� �Լ�

void* t_function1(void* data); // ������ȭ �� ����� �Է� �Լ�
void start_thread2(); // ������ ���� �Լ�
void end_thread2(); // ������ ���� �Լ�

