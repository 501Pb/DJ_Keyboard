#include <iostream>
#include <windows.h>
#include <irrKlang.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <ctime>

using namespace irrklang;
using namespace std;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


void musicStart(vector<vector<int> > & note, ISoundEngine * music);


int main(int argc, const char** argv) {
	// start the sound engine with default parameters
	ISoundEngine * music = createIrrKlangDevice();
	system("cls");
	srand((unsigned int)time(0));

	// Maximum sound count at once
	int nesting = 3;

	vector<vector<int> > note(32, vector<int>(nesting,0));
	cout << "Now Playing~";
	
	musicStart(note, music);
	Sleep(1000);
	music->drop();
	return 0;
}

void musicStart(vector<vector<int> > & note, ISoundEngine * music) {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < note[i].size(); j++) {
			note[i][j] = rand() % 15;
			//cout << note[i][j] << " ";
		}
		//cout << endl;
	}

	// Kick
	note[0][0] = note[2][0] = note[8][0] = note[10][0] = note[16][0] = note[21][0] = note[23][0] = note[24][0] = note[26][0] = 100;
	// Snare
	note[4][1] = note[12][1] = note[20][1] = note[28][1] = 101;
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
		Sleep(250);
	}
}
