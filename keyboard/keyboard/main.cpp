#include "DJ.h"

int main(void) {

	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ
	system("cls");

	while (1) {
		if(menu_function() == 1) break; //menu_function()�Լ��� 1�� ��ȯ�ϸ� ���� ������.
	}
	return 0;
}