#include "DJ.h"
#include "music.h"
#include "Recording.h"

int main(void) {

	game_init();//°ÔÀÓ ÃÊ±â¼³Á¤

	game_status status = game_status::Init; // ê²Œì„ ?íƒœ ?œì‹œ
	string filename = "music";	// filename ?€??
	thread thread_recording(Record, &status, &filename); // ?¹ìŒ???°ë ˆ??
	
	srand((unsigned int)time(0) * (unsigned int)GetCurrentThreadId());

	game_init();//ê²Œì„ ì´ˆê¸°?¤ì •
	
	Music music = Music();
        // music thread
	thread music_thread(&Music::music_start, &music);
	
	system("cls");
		
	
	while (1) {
		status = game_status::Start;

		if (!menu_function())
			break;

		status = game_status::GameOver;
	} //°ÔÀÓ¿À¹ö ´çÇÒ¶§±îÁö
	
	status = game_status::End;

	thread_recording.join(); // ?°ë ˆ??ì¢…ë£Œê¹Œì? ?€ê¸?


	return 0;
}
