#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_status status = game_status::Init; // 게임 상태 표시
	string filename = "music";	// filename 저장
	thread thread_recording(Record, &status, &filename); // 녹음용 쓰레드
	
	game_init();//게임 초기설정
	title();//타이틀
	system("cls");
			
	while (1) {
		status = game_status::Start;

		if (menu_function() == 1) break; //menu_function()함수가 1을 반환하면 게임 종료함.
		
		status = game_status::GameOver;
	}

	status = game_status::End;
	thread_recording.join(); // 쓰레드 종료까지 대기

	return 0;
}