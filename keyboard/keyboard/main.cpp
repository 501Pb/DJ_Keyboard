#include "DJ.h"
#include "music.h"
#include "Recording.h"

int main(void) {

	game_init();//���� �ʱ⼳��

	game_status status = game_status::Init; // 게임 ?�태 ?�시
	string filename = "music";	// filename ?�??
	thread thread_recording(Record, &status, &filename); // ?�음???�레??
	
	srand((unsigned int)time(0) * (unsigned int)GetCurrentThreadId());

	game_init();//게임 초기?�정
	
	Music music = Music();
        // music thread
	thread music_thread(&Music::music_start, &music);
	
	system("cls");
		
	
	while (1) {
		status = game_status::Start;

		if (!menu_function())
			break;

		status = game_status::GameOver;
	} //���ӿ��� ���Ҷ�����
	
	status = game_status::End;

	thread_recording.join(); // ?�레??종료까�? ?��?


	return 0;
}
