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

void music_start(vector<vector<int> > & note, ISoundEngine * music, int & bpm, bool & playing) {
	while (playing) {
		for (vector<int> beat : note) {
			for (int sound : beat) {
				if (sound == 0) continue;
				switch (sound) {
				case 1:
					music->play2D("./music/LowDo.wav", false);
					break;
				case 2:
					music->play2D("./music/LowLe.wav", false);
					break;
				case 3:
					music->play2D("./music/LowMi.wav", false);
					break;
				case 4:
					music->play2D("./music/LowFa.wav", false);
					break;
				case 5:
					music->play2D("./music/LowSol.wav", false);
					break;
				case 6:
					music->play2D("./music/LowLa.wav", false);
					break;
				case 7:
					music->play2D("./music/LowSi.wav", false);
					break;
				case 8:
					music->play2D("./music/Do.wav", false);
					break;
				case 9:
					music->play2D("./music/Le.wav", false);
					break;
				case 10:
					music->play2D("./music/Mi.wav", false);
					break;
				case 11:
					music->play2D("./music/Fa.wav", false);
					break;
				case 12:
					music->play2D("./music/Sol.wav", false);
					break;
				case 13:
					music->play2D("./music/La.wav", false);
					break;
				case 14:
					music->play2D("./music/Si.wav", false);
					break;
				case 100:
					music->play2D("./music/Kick.wav", false);
					break;
				case 101:
					music->play2D("./music/Snare.wav", false);
					break;
				default:
					break;
				}
			}
			Sleep(60000 / (2 * bpm));
		}
	}
}

void music_changer(vector<vector<int> > & note, int length) {
	cout << "[+] length : " << length << endl;
	int start = rand() % 32;
	for (int i = 0; i < length; i++) {
		int sound = rand() % 14 + 1;
		note_push(note[start % 32], sound);
		cout << "Add " << sound << " at " << start << endl;
		++start;
	}
}

void note_push(vector<int> & note, int sound) {
	for (int i = 2; i < note.size() - 1; i++) {
		note[i + 1] = note[i];
	}
	note[2] = sound;
}

void clear_note(vector<vector<int> > & note, int nesting) {
	note.assign(32, vector<int>(nesting + 2, 0));
	// Kick
	note[0][0] = note[2][0] = note[8][0] = note[10][0] = note[16][0] = note[21][0] = note[23][0] = note[24][0] = note[26][0] = 100;
	// Snare
	note[4][1] = note[12][1] = note[20][1] = note[28][1] = 101;
}
