#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <windows.h>
#include <irrKlang.h>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <thread>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;
using namespace std;

static const char* SOUND[17] = {
	"",
	"./music/LowDo.wav",
	"./music/LowLe.wav",
	"./music/LowMi.wav",
	"./music/LowFa.wav",
	"./music/LowSol.wav",
	"./music/LowLa.wav",
	"./music/LowSi.wav",
	"./music/Do.wav",
	"./music/Le.wav",
	"./music/Mi.wav",
	"./music/Fa.wav",
	"./music/Sol.wav",
	"./music/La.wav",
	"./music/Si.wav",
	"./music/Kick.wav",
	"./music/Snare.wav"
};

class Music{
private:
	ISoundEngine * music;
	vector<vector<int> > note;
	int nesting;
	int bpm;
	bool playing;
	int beat;
	bool optionSoundErase;
	void note_push(vector<int> & note, int sound);

public:
	Music(int nesting = 2, int bpm = 130, bool option1 = true);
	void music_start();
	void music_stop() { playing = false; }
	void bpm_changer(int bpm) { this->bpm = bpm; }
	void note_adder(int length);
	void note_clear();
	~Music() { music->drop(); }

};

#endif
