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
	Music music = Music();
	system("cls");

	cout << "Now Playing~" << endl;
	cout.flush();

	srand((unsigned int)time(0) * (unsigned int)GetCurrentThreadId());

	// music thread
	thread music_thread(&Music::music_start, &music);

	// input
	while (1) {
		cout << "Insert length :";
		int len;
		cin >> len;
		music.note_adder(len);
	}

	music_thread.join();
	return 0;
}
