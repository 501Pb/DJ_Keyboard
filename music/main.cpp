#include "music.h"
#include <iostream>
#include <windows.h>
#include <irrKlang.h>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <thread>

using namespace irrklang;
using namespace std;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


int main(int argc, const char** argv) {
	// start the sound engine with default parameters
	ISoundEngine * music = createIrrKlangDevice();

	system("cls");

	// Maximum sound count at once
	int nesting = 2;
	
	int bpm = 130;

	bool playing = true;

	vector<vector<int> > note;
	clear_note(note, nesting);

	cout << "Now Playing~" << endl;
	cout.flush();
	srand((unsigned int)time(0) * (unsigned int)GetCurrentThreadId());

	thread music_thread(music_start, ref(note), music, ref(bpm), ref(playing));
	while (1) {
		music_changer(note, rand()%5 + 1);
		Sleep(5000);
		// change speed
		bpm += 5;
	}

	music_thread.join();

	music->drop();
	return 0;
}
