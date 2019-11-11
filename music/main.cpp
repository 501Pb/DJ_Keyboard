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
	clearNote(note, nesting);

	cout << "Now Playing~";
	cout.flush();

	thread music_thread(musicStart, ref(note), music, bpm, ref(playing));
	thread change_thread(musicChanger, ref(note), 5);
	thread change_thread2(musicChanger, ref(note), 5);
	thread change_thread3(musicChanger, ref(note), 5);

	music_thread.join();
	change_thread.join();
	change_thread2.join();
	change_thread3.join();

	music->drop();
	return 0;
}
