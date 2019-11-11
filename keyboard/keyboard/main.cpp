#include "DJ.h"

int main(void) {

	game_init();//게임 초기설정
	title();//타이틀
	system("cls");

	while (1) {
		if(menu_function() == 1) break; //menu_function()함수가 1을 반환하면 게임 종료함.
	}
	return 0;
}