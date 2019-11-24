#include "DJ.h"
#include "music.h"
#include "Recording.h"

int main(void) {
	game_status status = game_status::Init; // 게임 상태 표시
	string filename = "music";	// filename 저장
	thread thread_recording(Record, &status, &filename); // 녹음용 쓰레드
	
	srand((unsigned int)time(0) * (unsigned int)GetCurrentThreadId());

	// music thread
	Music* music = new Music();
	thread music_thread(&Music::music_start, music);
	
	game_init();//게임 초기설정
	title();//타이틀
	system("cls");
		
	
	do {
		status = game_status::Start;
		
		play_game();

		status = game_status::GameOver;
	} while (game_over());//게임오버 당할때까지
	
	status = game_status::End;
	thread_recording.join(); // 쓰레드 종료까지 대기

	return 0;
}
