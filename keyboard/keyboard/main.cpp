#include "DJ.h"
#include "music.h"
#include "Recording.h"

extern Music music;

int main(void) {


	game_init();

	game_status status = game_status::Init;
	string filename = "music";
	thread thread_recording(Record, &status, &filename);
	
	srand((unsigned int)time(0) * (unsigned int)GetCurrentThreadId());

	game_init();
	
    // music thread
	thread music_thread(&Music::music_start, &music);
	
	system("cls");
		
	
	while (1) {
		status = game_status::Start;

		if (!menu_function())
			break;

		status = game_status::GameOver;
	} 
	
	music.music_stop();
	status = game_status::End;

	music_thread.join();
	thread_recording.join();
	
	music.~Music();
	return 0;
}
