#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_status status = Init; // 게임 상태 표시
	std::thread thread_recording(Record, &status); // 녹음용 쓰레드
	
	game_init();//게임 초기설정
	title();//타이틀
	system("cls");

	
	do {
		status = Start;
		
		play_game();

		status = GameOver;
	} while (game_over());//게임오버 당할때까지
	
	status = End;
	thread_recording.join(); // 쓰레드 종료까지 대기

	return 0;
}