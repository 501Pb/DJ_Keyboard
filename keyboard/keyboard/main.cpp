#include "DJ.h"

int main(void) {
	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ

	cout << "Word List" << endl<<endl;
	InitData();

	make_random();

	Sleep(10000);
	system("cls");

	do {
		play_game();
	} while (game_over());//���ӿ��� ���Ҷ�����

	return 0;
}