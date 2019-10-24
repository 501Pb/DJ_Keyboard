#define MAX_NUM 3
#include <iostream>
#include <windows.h>//sleep()
#include <conio.h>//getch() - 키입력
using namespace std;

int speed = 0;

void title(void);
void game_init(void);
//*미구현*//
void game_over(void);

//할까말까
void new_block(void); //새로운 블록을 하나 만듦 
void check_key(void); //키보드로 키를 입력받음 
void drop_block(void); //블록을 아래로 떨어트림 

int main(void) {
	game_init();
	title();



	return 0;
}


void game_init(void) {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void title(void) {
	cout << "\n\n\n\n";
	cout << "\t ______       ___          ___   _  _______  __   __  _______  _______  _______  ______    ______  " << endl;
	cout << "\t |      |     |   |        |   | | ||       ||  | |  ||  _    ||       ||   _   ||    _ |  |      | " << endl;
	cout << "\t |  _    |    |   |        |   |_| ||    ___||  |_|  || |_|   ||   _   ||  |_|  ||   | ||  |  _    |" << endl;
	cout << "\t |  _    |    |   |        |   |_| ||    ___||  |_|  || |_|   ||   _   ||  |_|  ||   | ||  |  _    |" << endl;
	cout << "\t | | |   |    |   |        |      _||   |___ |       ||       ||  | |  ||       ||   |_||_ | | |   |" << endl;
	cout << "\t | |_|   | ___|   |        |     |_ |    ___||_     _||  _   | |  |_|  ||       ||    __  || |_|   |" << endl;
	cout << "\t |       ||       | _____  |    _  ||   |___   |   |  | |_|   ||       ||   _   ||   |  | ||       |" << endl;
	cout << "\t |______| |_______||_____| |___| |_||_______|  |___|  |_______||_______||__| |__||___|  |_||______| " << endl;
	cout << "\n\n\n\n";

	while (1) {
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(1000);
		cout << "\r\t \t \t \t \t \t                 ";
		Sleep(1000);
		if (_kbhit()) {
			_getch();
			break;
		}
	}
	system("cls");
}