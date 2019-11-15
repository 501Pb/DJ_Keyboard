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
#pragma comment(lib, "irrKlang.lib")

Music::Music(int nesting, int bpm, bool option1) {
	music = createIrrKlangDevice();
	this->bpm = bpm;
	optionSoundErase = option1;
	playing = true;
	note.assign(32, vector<int>(nesting + 2, 0));
	// Kick
	note[0][0] = note[2][0] = note[8][0] = note[10][0] = note[16][0] = note[21][0] = note[23][0] = note[24][0] = note[26][0] = 15;
	// Snare
	note[4][1] = note[12][1] = note[20][1] = note[28][1] = 16;
}

void Music::music_start() {
	while (playing) {
		for (beat = 0; beat < 32; beat++) {
			if (!playing) break;
			for (int& sound : note[beat]) {
				if (sound == 0) continue;
				music->play2D(SOUND[sound], false);				
				// with following option every sound play only once
				//*/
				if (optionSoundErase && sound != 15 && sound != 16) {
					sound = 0;
				}
				//*/
			}
			// bpm calculate
			Sleep(60000 / (2 * bpm));
		}
	}
}

void Music::note_adder(int length) {
	cout << "[+] length : " << length << endl;
	// adding after present beat
	int start = beat + 1 ;
	for (int i = 0; i < length; i++) {
		int sound = rand() % 14 + 1;
		note_push(note[start % 32], sound);
		cout << "Add " << sound << " at " << start%32 << endl;
		++start;
	}
}

void Music::note_push(vector<int> & note, int sound) {
	for (int i = 2; i < note.size() - 1; i++) {
		note[i + 1] = note[i];
	}
	note[2] = sound;
}
