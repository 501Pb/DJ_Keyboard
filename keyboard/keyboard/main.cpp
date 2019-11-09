#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_init();//게임 초기설정
	title();//타이틀
	system("cls");

	game_status status = game_status::Start;

	do {
		std::thread thread_recording(Record, &status);
		
		play_game();

		status = game_status::End;
	} while (game_over());//게임오버 당할때까지
	thread_recording.join();

	return 0;
}