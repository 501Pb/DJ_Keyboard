#include "DJ.h"

int main(void) {
	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ
	system("cls");

	do {

		play_game();
	} while (game_over());//���ӿ��� ���Ҷ�����

	return 0;
}