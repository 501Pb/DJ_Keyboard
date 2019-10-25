#include "DJ.h"

int main(void) {
	game_init();//게임 초기설정
	title();//타이틀
	system("cls");

	do {

		play_game();
	} while (game_over());//게임오버 당할때까지

	return 0;
}